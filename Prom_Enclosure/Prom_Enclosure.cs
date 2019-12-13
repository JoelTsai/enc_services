using System;
using System.ServiceProcess;
using System.IO;
using System.Management;
using System.Diagnostics;
using Enclsoure;
using Microsoft.Win32;
using System.Collections.Generic;
using System.Timers;
using System.Threading;

namespace Prom_Enclosure_Serives
{
    public partial class Prom_EnclosureS : ServiceBase
    {
        private System.Timers.Timer Enclosure_update_timer;
        public Enclsoure_class Enclosure;
        public Dictionary<string, uint?[]> AllData;
        public uint?[] GetRegFan;// GetRegFan.Length = 4 * Fan.Length
        public uint?[] GetRegTemperature;// GetRegTemperature.Length = 4 * Temperature.Length
        public uint?[] GetRegVoltage;// GetRegVoltage.Length = 4 * Voltage.Length
        public uint?[] GetRegLed;
        //public uint?[] GetRegLed_init;

        public uint?[] Controller_Temp_threshold;
        public uint?[] HDD_Temp_threshold;
        public static bool process_flag = false;

        public static string TimeParameter = "30";
        private WqlEventQuery query;
        private ManagementEventWatcher Registry_Watcher;

        public int interval = -1;// This value will not be changed if no "-i" in args.
                                 //  public Prom_EnclosureS Enc_Service;
        private Thread Blink_thread;
        private static System.Timers.Timer Blink_timer;
        public Prom_EnclosureS()
        {
            Blink_thread = new Thread(Blink_test);

            InitializeComponent();

            if (!EventLog.SourceExists("Promise"))
            {
                EventLog.CreateEventSource("Promise", "Promise_event");
            }

        }

        private void Reg_event()
        {
            query = new WqlEventQuery(@"SELECT * FROM RegistryKeyChangeEvent WHERE Hive='HKEY_LOCAL_MACHINE' AND KeyPath='SOFTWARE\\Pro_HWMonitor'");
            try
            {
                Registry_Watcher = new ManagementEventWatcher(query);
                Registry_Watcher.EventArrived += new EventArrivedEventHandler(ChkReqRoutine);
                Registry_Watcher.Start();
            }
            catch
            {
                Console.WriteLine("FAIL REG");
                return;
            }
        }

        protected override void OnStart(string[] args)
        {
            RegistryKey localKey = null, softwareKey = null, key4Driver = null;
            Process curProcess = Process.GetCurrentProcess();
            var procs = Process.GetProcesses();
            Log_File.FileLog("curProcess Name" + curProcess.ProcessName + "ID"+ curProcess.Id);
            foreach (var proc in procs)
            {
                if (proc.Id != curProcess.Id && proc.ProcessName == curProcess.ProcessName)
                {
                    Log_File.FileLog("detect process in background at Onstart & kill it : Name:" + proc.ProcessName+ "ID:"+ proc.Id);
                    proc.Kill();
                    Log_File.FileLog("kill process done");
                }
            }

            try
            {
                localKey = RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.LocalMachine, RegistryView.Registry64);
                softwareKey = localKey.OpenSubKey("SOFTWARE", true);
                key4Driver = softwareKey.CreateSubKey("Pro_HWMonitor", RegistryKeyPermissionCheck.ReadWriteSubTree);
                Enclsoure_class.Model_ID = Convert.ToUInt16(key4Driver.GetValue("Enc_Model"));
            }
            finally
            {
                if (key4Driver != null) key4Driver.Close();
                if (softwareKey != null) softwareKey.Close();
                if (localKey != null) localKey.Close();
            }

            this.Enclosure = new Enclsoure_class();

            
            try
            {
                localKey = RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.LocalMachine, RegistryView.Registry64);
                softwareKey = localKey.OpenSubKey("SOFTWARE", true);
                key4Driver = softwareKey.CreateSubKey("Pro_HWMonitor", RegistryKeyPermissionCheck.ReadWriteSubTree);
                key4Driver.SetValue("Enc_Model", Enclsoure_class.Model_ID, RegistryValueKind.DWord);
                if (key4Driver == null)
                    throw new Exception("Unable to create or open registry key");
            }
            finally
            {
                if (key4Driver != null) key4Driver.Close();
                if (softwareKey != null) softwareKey.Close();
                if (localKey != null) localKey.Close();
            }

            if (Prom_Enclosure_Serives.Program.SUP_EVT == true)
             {
                 Program.Pro_Event_viewer.WriteEntry("Enc_Service started... TimeParameter= \"" + TimeParameter + "\"\n");
             }
             Log_File.FileLog("Service is Start!JOEL");

            Blink_timer = new System.Timers.Timer
            {
                Interval = 1 * 1000
            };
           // aaa.Elapsed += Enclosure.Blink;

            // Enc_Service = new Prom_EnclosureS();
            uint time = Convert.ToUInt32(TimeParameter) * 1000;
             time = time <= 0 ? 1 : time;
            if (Enclsoure.Enclsoure_class.Model_ID != 0xFFFF)
            {
                Reg_event();


                GetRegistry("Init");
                Enclosure.Enclosure_SET_led(GetRegLed);
            }
            try
            {

                Enclosure_update_timer = new System.Timers.Timer
                {
                    Interval = time
                };
                Enclosure_update_timer.Elapsed += new ElapsedEventHandler(Enclosure_Services_update);
                Enclosure_update_timer.Start();
            }
            catch (Exception e)
            {
                Log_File.FileLog(Convert.ToString(e));
            }
        }

        protected override void OnStop()
        {
            Enclosure_update_timer.Stop();

            Enclosure.PD_OC_blink_thread.Abort();
            if (Enclsoure_class.GlobeError_LED_trigger == false)
            {
                Enclosure.tca6416.NCT6414_FAN_Control(Chip.Contrl.TCA6416_Constants.ENC_LED_GLOBE_ERR, Chip.Contrl.TCA6416_Constants.ENC_LED_GREEN);
            }
            Enclosure.GetEnclosureData(ref AllData);
            SetToREG();//Do Final update;
            if(Prom_Enclosure_Serives.Program.SUP_EVT == true)
            {
                try
                {
                    Program.Pro_Event_viewer.WriteEntry("Enc_Service stopped...");
                }
                catch (Exception e)
                {
                    Program.Pro_Event_viewer.WriteEntry("Stop Management Event Watcher failed...");
                    Program.Pro_Event_viewer.WriteEntry(Convert.ToString(e));
                }
            }
            this.Dispose();
        }

        private void Enclosure_Services_update(object sender, ElapsedEventArgs e)
        {
            //enc_Service = new Enc_Service();
            Enc_Main(); 
        }

        public void Enclosure_Console_update()
        {
            RegistryKey localKey = null, softwareKey = null, key4Driver = null;
            try
            {
                localKey = RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.LocalMachine, RegistryView.Registry64);
                softwareKey = localKey.OpenSubKey("SOFTWARE", true);
                key4Driver = softwareKey.CreateSubKey("Pro_HWMonitor", RegistryKeyPermissionCheck.ReadWriteSubTree);
                Enclsoure_class.Model_ID = Convert.ToUInt16(key4Driver.GetValue("Enc_Model"));
                if (key4Driver == null)
                    throw new Exception("Unable to create or open registry key");
            }
            finally
            {
                if (key4Driver != null) key4Driver.Close();
                if (softwareKey != null) softwareKey.Close();
                if (localKey != null) localKey.Close();
            }
            this.Enclosure = new Enclsoure_class();


            try
            {
                localKey = RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.LocalMachine, RegistryView.Registry64);
                softwareKey = localKey.OpenSubKey("SOFTWARE", true);
                key4Driver = softwareKey.CreateSubKey("Pro_HWMonitor", RegistryKeyPermissionCheck.ReadWriteSubTree);
                key4Driver.SetValue("Enc_Model", Enclsoure_class.Model_ID, RegistryValueKind.DWord);
                if (key4Driver == null)
                    throw new Exception("Unable to create or open registry key");
            }
            finally
            {
                if (key4Driver != null) key4Driver.Close();
                if (softwareKey != null) softwareKey.Close();
                if (localKey != null) localKey.Close();
            }

            while (true)
            {
                Console.WriteLine("psuNum:");
                uint psuNum = Convert.ToUInt32(Console.ReadLine());
                Console.WriteLine("status:");
                uint status = Convert.ToUInt32(Console.ReadLine());
                if (psuNum == 99)
                    return;

                Enclosure.PSU.PSUSetFanSpeed(psuNum,status);
            }


            Blink_timer = new System.Timers.Timer
            {
                Interval = 1 * 1000
            };
          //  aaa.Elapsed += Enclosure.Blink;

            if (Enclsoure.Enclsoure_class.Model_ID != 0xFFFF)
            {
                Reg_event();

                GetRegistry("Init");
                Enclosure.Enclosure_SET_led(GetRegLed);
            } 
            Enc_Main();
        }

        public void Close()
        {
            Console.WriteLine("Computer has already been displosed.");
        }

        public  void Enc_Main()
        {
            // This value will not be changed if no "-i" in args.
            if (interval >= 0)
            {
                // Exit if this application is already running in another process.
                Process curProcess = Process.GetCurrentProcess();
                var procs = Process.GetProcesses();
                foreach (var proc in procs)
                {
                    if (proc.Id != curProcess.Id && proc.ProcessName == curProcess.ProcessName)
                    {
                        Console.WriteLine("This application is already running as process {0}", proc.Id);
                        OnStop();
                    }
                }
            }
            do
            {
                Console.WriteLine("----------------------------v0.1");
                    Enclosure.GetEnclosureData(ref AllData);
                    SetToREG();
                    if (interval > 0)
                      Thread.Sleep(interval * 1000);

            } while (interval >= 0);

            process_flag = true;
        }



        private static UInt32 VoltageToU32(byte voltage)
        {
            UInt32 high = (UInt32)(voltage >> 4);
            UInt32 low = (UInt32)(voltage & 0x0F);
            return ((high << 16) | low);
        }

        private void SetToREG()
        {
            try
            {
                RegistryKey localKey = null, softwareKey = null, key4Driver = null;

                try
                {
                    // RegistryKey for FW
                    localKey = RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.LocalMachine, RegistryView.Registry64);
                    softwareKey = localKey.OpenSubKey("SOFTWARE", true);
                    key4Driver = softwareKey.CreateSubKey("Pro_HWMonitor", RegistryKeyPermissionCheck.ReadWriteSubTree);
                    if (key4Driver == null)
                        throw new Exception("Unable to create or open registry key");
                    Update(key4Driver);
                }
                finally
                {
                    if (key4Driver != null) key4Driver.Close();
                    if (softwareKey != null) softwareKey.Close();
                    if (localKey != null) localKey.Close();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Log_File.FileLog("SetToREG_FAIL:" + Convert.ToString(ex));
            }
        }

        //public void ChkReqRoutine(object sender, EventArrivedEventArgs e)
        public void ChkReqRoutine(object sender, EventArrivedEventArgs e)
        {
            Console.WriteLine("reg Chang!!!");
            bool request_flag = false;
            if (GetRegistry("FanConfig"))
            {
                Enclosure.Enclosure_SET_fan(GetRegFan);
                //request_flag = true;
            } 
            if (GetRegistry("LedConfig"))
            {

                //Enclosure.Enclosure_SET_led(GetRegLed);
                request_flag = true;
            }
            if (GetRegistry("NetLEDConfig"))
            {

                //Enclosure.Enclosure_SET_led(GetRegLed);
                request_flag = true;
            }
            if (GetRegistry("OPASLEDConfig"))
            {

                //Enclosure.Enclosure_SET_led(GetRegLed);
                request_flag = true;
            }
            if (request_flag)
            {
               
                Enclosure.Enclosure_SET_led(GetRegLed);
                request_flag = false;
            }

            if (GetRegistry("Control_Temp_threshold"))
            {
                Enclosure.Enclosure_SET_Control_Temp_threshold(Controller_Temp_threshold);
                //request_flag = true;
            }
            if (GetRegistry("HDD_Temp_threshold"))
            {
                Enclosure.Enclosure_SET_HDD_Temp_threshold(HDD_Temp_threshold);
                //request_flag = true;
            }

            if (GetRegistry("LocateLEDConfig"))
            {

                if (Blink_thread.IsAlive)
                {
                    Console.WriteLine("Locate thread alive");
                    Blink_timer.Stop();
                    Blink_thread.Abort();
                }

                if(!Blink_thread.IsAlive)
                {
                    Console.WriteLine("Locate thread non-alive");
                    Blink_thread = new Thread(Blink_test);
                }
                Blink_thread.Start();

               // t1.Abort();
               //request_flag = true;
            }

            //return request_flag;
        }
        private void Blink_test()
        {
            Enclosure.Locate_Blink();


           /* aaa.Start();
            Thread.Sleep(1000*15);
            aaa.Stop();*/
        }

       /* private static void Blink(Object source, ElapsedEventArgs e)
        {


                Console.WriteLine("new thread");
                Thread.Sleep(1000);

        }*/

        private bool GetRegistry(string unit)
        {

            byte[] RegValue = null;

            RegValue = null;
            switch (unit)
            {
                case "FanConfig":
                    try
                    {
                        if (!GetRegValue(unit, ref RegValue))
                        {
                            //Console.WriteLine("The unit {0} should not to change !", unit);
                            return false;
                        }
                        else
                        {
                            GetRegFan = new uint?[RegValue.Length / 4];
                            for (int i = 0; i < RegValue.Length; i++)
                            {
                                if (i % 4 == 0)
                                {
                                    int FanLevel = RegValue[i + 2];
                                    int FanCount = RegValue[i];
                                    int FanSpeed = (FanLevel << 16) + FanCount;
                                    Console.WriteLine("FanLevel = {01:x}  FanCount = {1:x} ", FanLevel, FanCount);
                                    GetRegFan[i / 4] = Convert.ToUInt32(FanLevel);
                                    Console.WriteLine("FanLevel[{0}] = {1:x} ", (i / 4), GetRegFan[i / 4]);
                                    //  Console.WriteLine("FanCount[{0}] = {1:x} ", (i / 4), FanCount);
                                    //  Console.WriteLine("FanSpeed[{0}] = {1:x} ", (i / 4), FanSpeed);
                                }
                                //Console.WriteLine("{0}[{1}] = {2:x} ", UnitName, i + 1, GetRegFan[i]);
                            }
                        }
                    }
                    catch (NullReferenceException ex)
                    {
                        return false;
                    }
                    break;
                case "Temperature":
                    try
                    {
                        if (!GetRegValue(unit, ref RegValue))
                        {
                            Console.WriteLine("The unit {0} should not to change !", unit);
                            return false;
                        }
                        else
                        {
                            GetRegTemperature = new uint?[RegValue.Length];
                            Console.WriteLine("RegValue.Length={0}", RegValue.Length);
                            for (int i = 0; i < RegValue.Length; i++)
                            {
                                if (i % 4 == 0)
                                {
                                    GetRegTemperature[i] = Convert.ToUInt32(RegValue[i]);
                                    Console.WriteLine("TemperatureReg[{0}] = {1:x} ", (i / 4), GetRegTemperature[i]);
                                }
                                //Console.WriteLine("{0}[{1}] = {2:x} ", UnitName, i + 1, GetRegTemperature[i]);
                            }
                        }
                    }
                    catch (NullReferenceException ex)
                    {
                        return false;
                    }
                    break;
                case "Voltage":
                    try
                    {
                        if (!GetRegValue(unit, ref RegValue))
                        {
                            Console.WriteLine("The unit {0} should not to change !", unit);
                            return false;
                        }
                        else
                        {
                            GetRegVoltage = new uint?[RegValue.Length];
                            for (int i = 0; i < RegValue.Length; i++)
                            {
                                if (i % 4 == 0)
                                {
                                    int volreg = ((RegValue[i + 2] << 4) | (RegValue[i]));
                                    GetRegVoltage[(i / 4)] = Convert.ToUInt32(volreg);
                                    Console.WriteLine("VoltageReg[{0}] = {1:x} ", (i / 4), volreg);
                                }
                                //Console.WriteLine("{0}[{1}] = {2:x} ", UnitName, i + 1, GetRegVoltage[i]);
                            }
                        }
                    }
                    catch (NullReferenceException ex)
                    {
                        return false;
                    }
                    break;
                case "Control_Temp_threshold":
                    try
                    {
                        if (!GetRegValue(unit, ref RegValue))
                        {
                            //Console.WriteLine("The unit {0} should not to change !", unit);
                            return false;
                        }
                        else
                        {
                            Controller_Temp_threshold = new uint?[RegValue.Length / 4];
                            for (int i = 0; i < RegValue.Length; i++)
                            {
                                if (i % 4 == 0)
                                {
                                    int Temp = RegValue[i + 2];
                                    Console.WriteLine("Control_Temp_threshold = {0:x}  ", Temp);
                                    Controller_Temp_threshold[i / 4] = Convert.ToUInt32(Temp);
                                }
                            }
                        }
                    }
                    catch(NullReferenceException ex)
                    {
                        uint i = 0x02;
                        RegistryKey localKey = null, softwareKey = null, key4Driver = null;
                        localKey = RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.LocalMachine, RegistryView.Registry64);
                        softwareKey = localKey.OpenSubKey("SOFTWARE", true);
                        key4Driver = softwareKey.OpenSubKey("Pro_HWMonitor", RegistryKeyPermissionCheck.ReadWriteSubTree);

                        using (MemoryStream buffer = new MemoryStream())
                        {
                            using (BinaryWriter writer = new BinaryWriter(buffer))
                            {
                                writer.Write((UInt32)i);
                                writer.Write(((UInt32)Enclsoure_class.Temp_OW_threshold)<<16);
                                writer.Write(((UInt32)Enclsoure_class.Temp_OC_threshold)<<16);
                                key4Driver.SetValue("Control_Temp_threshold", buffer.ToArray(), RegistryValueKind.Binary);
                            }
                        }
                        key4Driver.Close();
                        softwareKey.Close();
                        localKey.Close();

                        return false;
                    }
                    break;
                case "HDD_Temp_threshold":
                    try
                    {
                        if (!GetRegValue(unit, ref RegValue))
                        {
                            //Console.WriteLine("The unit {0} should not to change !", unit);
                            return false;
                        }
                        else
                        {
                            HDD_Temp_threshold = new uint?[RegValue.Length / 4];
                            for (int i = 0; i < RegValue.Length; i++)
                            {
                                if (i % 4 == 0)
                                {
                                    int Temp = RegValue[i + 2];
                                    Console.WriteLine("Control_Temp_threshold = {0:x}  ", Temp);
                                    HDD_Temp_threshold[i / 4] = Convert.ToUInt32(Temp);
                                }
                            }
                        }
                    }
                    catch (NullReferenceException ex)
                    {
                        uint i = 0x02;
                        RegistryKey localKey = null, softwareKey = null, key4Driver = null;
                        localKey = RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.LocalMachine, RegistryView.Registry64);
                        softwareKey = localKey.OpenSubKey("SOFTWARE", true);
                        key4Driver = softwareKey.OpenSubKey("Pro_HWMonitor", RegistryKeyPermissionCheck.ReadWriteSubTree);

                        using (MemoryStream buffer = new MemoryStream())
                        {
                            using (BinaryWriter writer = new BinaryWriter(buffer))
                            {
                                writer.Write((UInt32)i);
                                writer.Write(((UInt32)Enclsoure_class.HDD_OW_threshold)<<16);
                                writer.Write(((UInt32)Enclsoure_class.HDD_OC_threshold)<<16);
                                key4Driver.SetValue("HDD_Temp_threshold", buffer.ToArray(), RegistryValueKind.Binary);
                            }
                        }
                        key4Driver.Close();
                        softwareKey.Close();
                        localKey.Close();

                        return false;
                    }
                    break;

                case "LedConfig":
                    try
                    {
                        if (!GetRegValue(unit, ref RegValue))
                        {
                            // Console.WriteLine("The unit {0} should not to change !", unit);
                            return false;
                        }
                        else
                        {
                            GetRegLed = new uint?[RegValue.Length / 4];
                            Console.WriteLine("RegValue.Length = [{0:x}]", RegValue.Length);
                            for (int i = 0; i < RegValue.Length; i += 4)
                            {
                                if (i % 4 == 0)
                                {
                                    int ledreg = ((RegValue[i + 2]) | (RegValue[i] << 8));

                                    GetRegLed[(i / 4)] = Convert.ToUInt32(ledreg);
                                    Console.WriteLine("i = [{0:x}]", i);
                                    Console.WriteLine("LedReg = [{0:x}]", ledreg);
                                }
                                //Console.WriteLine("{0}[{1}] = {2:x} ", UnitName, i + 1, GetRegVoltage[i]);
                            }
                        }
                    }
                    catch (NullReferenceException ex)
                    {
                        return false;
                    }
                    break;

                case "NetLEDConfig":
                    try
                    {
                        if (!GetRegValue(unit, ref RegValue))
                        {
                            // Console.WriteLine("The unit {0} should not to change !", unit);
                            return false;
                        }
                        else
                        {
                            Enclsoure_class.NET_LED = Convert.ToUInt32(RegValue[2]) & Chip.Contrl.TCA6416_Constants.NET_REQUEST_MASK;
                            Console.WriteLine("Enclsoure_class.NET_LED=[{0:x}]", Enclsoure_class.NET_LED);
                        }
                    }
                    catch (NullReferenceException ex)
                    {
                        return false;
                    }
                    break;

                case "OPASLEDConfig":
                    try
                    {
                        if (!GetRegValue(unit, ref RegValue))
                        {
                            // Console.WriteLine("The unit {0} should not to change !", unit);
                            return false;
                        }
                        else
                        {
                            Enclsoure_class.OPAS_LED = Convert.ToUInt32(RegValue[0]) & Chip.Contrl.TCA6416_Constants.OPAS_REQUEST_MASK;
                            Console.WriteLine("Enclsoure_class.OPAS_LED=[{0:x}]", Enclsoure_class.OPAS_LED);
                        }
                    }
                    catch (NullReferenceException ex)
                    {
                        return false;
                    }
                    break;

                case "Init":
                    try//try to get LED previous status
                    {
                        GetRegValue("LedConfig", ref RegValue);

                        GetRegLed = new uint?[RegValue.Length / 4];
                        Console.WriteLine("!!RegValue.Length = [{0:x}]", RegValue.Length);

                        for (int i = 0; i < RegValue.Length; i += 4)
                        {
                            if (i % 4 == 0)
                            {
                                int ledreg = ((RegValue[i + 2]) | (RegValue[i] << 8));
                                GetRegLed[(i / 4)] = (uint)(i / 4);
                                GetRegLed[(i / 4)] = Convert.ToUInt32(ledreg);
                                Console.WriteLine("i = [{0:x}]", i);
                                Console.WriteLine("LedReg = [{0:x}]", ledreg);
                            }
                            //Console.WriteLine("{0}[{1}] = {2:x} ", UnitName, i + 1, GetRegVoltage[i]);
                        }
                        for (int i = 0; i < GetRegLed.Length; i++)
                        {
                            Console.WriteLine("GetRegLed_init[{0}]={1:x}", i, GetRegLed[i]);
                        }
                    }
                    catch (Exception)
                    {
                        GetRegLed = new uint?[2];
                        for (int i = 0; i < GetRegLed.Length / GetRegLed.Rank; i++)
                        {
                            for (int j = 0; j < GetRegLed.Rank; j++)
                                GetRegLed[i] = 0;
                        }

                        for (int i = 0; i < GetRegLed.Length; i++)
                        {
                            Console.WriteLine("GetRegLed[{0}]={1:x}", i, GetRegLed[i]);
                        }
                    }

                    try//try to get OPAS previous status
                    {
                        GetRegValue("OPASLEDConfig", ref RegValue);
                        Enclsoure_class.OPAS_LED = Convert.ToUInt32(RegValue[0]) & Chip.Contrl.TCA6416_Constants.OPAS_REQUEST_MASK;
                    }
                    catch (Exception)
                    {
                        Enclsoure_class.OPAS_LED = 0x00;
                    }

                    try//try to get NETwork previous status
                    {
                        GetRegValue("NetLEDConfig", ref RegValue);
                        Enclsoure_class.NET_LED = Convert.ToUInt32(RegValue[2]) & Chip.Contrl.TCA6416_Constants.NET_REQUEST_MASK;
                    }
                    catch (Exception)
                    {
                        Enclsoure_class.NET_LED = 0x00;
                    }

                    try //try to get Control_Temp_threshold previous status
                    {
                        RegValue = null;
                        GetRegValue("Control_Temp_threshold", ref RegValue);
                        Controller_Temp_threshold = new uint?[RegValue.Length / 4];
                        for (int i = 0; i < RegValue.Length; i++)
                        {
                            if (i % 4 == 0)
                            {
                                int Temp = RegValue[i + 2];
                                Controller_Temp_threshold[i / 4] = Convert.ToUInt32(Temp);
                            }
                        }
                        Enclosure.Enclosure_SET_Control_Temp_threshold(Controller_Temp_threshold);
                    }
                    catch(Exception)
                    {
                        Console.WriteLine("Control_Temp_threshold FAIL");
                    }

                    try //try to get HDD_Temp_threshold previous status
                    {
                        RegValue = null;
                        GetRegValue("HDD_Temp_threshold", ref RegValue);
                        HDD_Temp_threshold = new uint?[RegValue.Length / 4];
                        for (int i = 0; i < RegValue.Length; i++)
                        {
                            if (i % 4 == 0)
                            {
                                int Temp = RegValue[i + 2];
                                HDD_Temp_threshold[i / 4] = Convert.ToUInt32(Temp);
                            }
                        }
                        Enclosure.Enclosure_SET_HDD_Temp_threshold(HDD_Temp_threshold);
                    }
                    catch (Exception)
                    {
                        Console.WriteLine("HDD_Temp_threshold FAIL");
                    }
                    break;

                case "LocateLEDConfig":

                    if (!GetRegValue(unit, ref RegValue))
                    {
                        // Console.WriteLine("The unit {0} should not to change !", unit);
                        return false;
                    }
                    else
                    {
                       for(int i=0;i<RegValue.Length; i++)
                            Console.WriteLine("GetRegLed[{0}]={1:x}", i, RegValue[i]);

                        Enclsoure_class.Locatemask[0, 0] = RegValue[0];
                        Enclsoure_class.Locatemask[0, 1] = RegValue[2];
                        Enclsoure_class.Locatemask[1, 0] = RegValue[4];
                        Enclsoure_class.Locatemask[1, 1] = RegValue[6];

                        for (int i=0;i<Enclsoure_class.Locatemask.Length/Enclsoure_class.Locatemask.Rank;i++)
                            for(int j=0;j<Enclsoure_class.Locatemask.Rank;j++)
                                Console.WriteLine("Locatemask[{0}][{1}] = [{2:x}]", i,j, Enclsoure_class.Locatemask[i,j]);
                    }
                    break;

                default:
                    break;
            }
            return true;
        }

        private bool GetRegValue(string UnitName, ref byte[] RegValue)
        {
            bool Trigger = false;
            try
            {
                RegistryKey localKey = null, softwareKey = null, key4Driver = null;

                localKey = RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.LocalMachine, RegistryView.Registry64);
                softwareKey = localKey.OpenSubKey("SOFTWARE", true);
                key4Driver = softwareKey.OpenSubKey("Pro_HWMonitor", RegistryKeyPermissionCheck.ReadWriteSubTree);

                byte[] ValueUnit = (byte[])key4Driver.GetValue(UnitName);


                RegValue = new byte[(ValueUnit[0] & 0x3F) * 4];
                //Console.WriteLine("Length=[{0}]", RegValue.Length);


                Trigger = (ValueUnit[0] & 0x80) == 0x80;


                for (int i = 0; i < RegValue.Length; i++)
                {
                    RegValue[i] = ValueUnit[i + 4];
                }
                if (Trigger)
                {
                    ValueUnit[0] = Convert.ToByte(Convert.ToInt16(ValueUnit[0]) & 0x7F);
                    key4Driver.SetValue(UnitName, ValueUnit, RegistryValueKind.Binary);
                }
                key4Driver.Close();
                softwareKey.Close();
                localKey.Close();
                return Trigger;
            }
            catch (NullReferenceException ex)
            {
                Console.WriteLine("{0} are not create", UnitName);
                throw ex;
                return false;
            }
            catch (Exception ex)
            {
                Console.WriteLine(" Cannot get reg {0},{1} ", UnitName, ex);
                return false;
            }
        }

        /**
         * Write the sensor data to registry
         */
        private void Update(RegistryKey key4Driver)
        {
            string[] subkeyNames = key4Driver.GetSubKeyNames();
            string[] valueNames = key4Driver.GetValueNames();

            foreach (KeyValuePair<string, uint?[]> kv in AllData)
            {
                using (MemoryStream buffer = new MemoryStream())
                {
                    using (BinaryWriter writer = new BinaryWriter(buffer))
                    {
                        try
                        {
                            switch (kv.Key)
                            {
                                case "Fan":
                                    writer.Write((UInt32)kv.Value.Length);
                                    for (int i = 0; i < kv.Value.Length; i++)
                                    {
                                        writer.Write((UInt32)kv.Value[i]);
                                    }

                                    key4Driver.SetValue(kv.Key, buffer.ToArray(), RegistryValueKind.Binary);
                                    break;
                                case "Control":
                                    break;
                                case "Voltage":
                                    writer.Write((UInt32)kv.Value.Length);
                                    for (int i = 0; i < kv.Value.Length; i++)
                                    {
                                        uint u32Voltage = VoltageToU32(Convert.ToByte(kv.Value[i]));
                                        writer.Write(u32Voltage);
                                    }
                                    key4Driver.SetValue(kv.Key, buffer.ToArray(), RegistryValueKind.Binary);
                                    break;
                                case "Temperature":
                                    writer.Write((UInt32)kv.Value.Length);
                                    for (int i = 0; i < kv.Value.Length; i++)
                                    {
                                        writer.Write((UInt32)kv.Value[i]);
                                    }
                                    key4Driver.SetValue(kv.Key, buffer.ToArray(), RegistryValueKind.Binary);
                                    break;
                                case "Led":
                                    if(Enclsoure_class.Blink_trigger)
                                        writer.Write((UInt32)kv.Value.Length|0x40);//notfication now are blink status
                                    else
                                        writer.Write((UInt32)kv.Value.Length);
                                    for (int i = 0; i < kv.Value.Length; i++)
                                    {
                                        writer.Write((UInt32)kv.Value[i]);
                                    }

                                    key4Driver.SetValue(kv.Key, buffer.ToArray(), RegistryValueKind.Binary);
                                    break;

                                default:
                                    break;
                            }
                        }
                        catch(Exception ex)
                        {
                            Console.WriteLine("Fail update date KEY:{0} cause:{1} ",kv.Key,ex);
                        }
                    }
                }
            }
        }
    }
}
