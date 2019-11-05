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

        public uint?[] Temp_threshold;
        public static bool process_flag = false;

        public static string TimeParameter = "30";

      //  public Prom_EnclosureS Enc_Service;

        public Prom_EnclosureS()
        {
            Program.Pro_Event_viewer.WriteEntry("hello in there");
            InitializeComponent();


            if (!EventLog.SourceExists("Promise"))
            {
                EventLog.CreateEventSource("Promise", "Promise_event");
            }
            
            this.Enclosure = new Enclsoure_class();
        }

        protected override void OnStart(string[] args)
        {

            Program.Pro_Event_viewer.WriteEntry("Enc_Service started...");
            Program.Pro_Event_viewer.WriteEntry("TimeParameter= \"" + TimeParameter + "\"\n");
            Log_File.FileLog("Service is Start!JOEL");
           // Enc_Service = new Prom_EnclosureS();

            WqlEventQuery query = new WqlEventQuery(@"SELECT * FROM RegistryKeyChangeEvent WHERE Hive='HKEY_LOCAL_MACHINE' AND KeyPath='SOFTWARE\\Pro_HWMonitor'");
            ManagementEventWatcher Registry_Watcher = new ManagementEventWatcher(query);
            Registry_Watcher.EventArrived += new EventArrivedEventHandler(ChkReqRoutine);


            GetRegistry("Init");
            Enclosure.Enclosure_SET_led(GetRegLed);
            try
            {
                Registry_Watcher.Start();
                Enclosure_update_timer = new System.Timers.Timer();
                Enclosure_update_timer.Interval = Convert.ToInt32(TimeParameter) * 1000;
                Enclosure_update_timer.Elapsed += new ElapsedEventHandler(Enclosure_update);
                Enclosure_update_timer.Start();
            }
            catch (Exception e)
            {
                Log_File.FileLog(Convert.ToString(e));
            }
        }

        protected override void OnStop()
        {
            Log_File.FileLog("Service is Stop!");
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

        private void Enclosure_update(object sender, ElapsedEventArgs e)
        {
            //enc_Service = new Enc_Service();
            Enc_Main();

           
        }

        public void Close()
        {
            Console.WriteLine("Computer has already been displosed.");
        }

        public  void Enc_Main()
        {
            int interval = -1; // This value will not be changed if no "-i" in args.

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
                    Console.WriteLine("----------------------------v0.1");
                    Enclosure.GetEnclosureData(ref AllData);
                    SetToREG();
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

            if (GetRegistry("Temp_threshold"))
            {
                Enclosure.Enclosure_SET_Temp_threshold(Temp_threshold);
                //request_flag = true;
            }

            //return request_flag;
        }

        private bool GetRegistry(string unit)
        {

            byte[] RegValue = null;

            RegValue = null;
            switch (unit)
            {
                case "FanConfig":
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
                    break;
                case "Temperature":
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
                    break;
                case "Voltage":
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
                    break;
                case "Temp_threshold":
                    if (!GetRegValue(unit, ref RegValue))
                    {
                        //Console.WriteLine("The unit {0} should not to change !", unit);
                        return false;
                    }
                    else
                    {
                        Temp_threshold = new uint?[RegValue.Length / 4];
                        for (int i = 0; i < RegValue.Length; i++)
                        {
                            if (i % 4 == 0)
                            {
                                int Temp = RegValue[i + 2];
                                Console.WriteLine("Temp_threshold = {0:x}  ", Temp);
                                Temp_threshold[i / 4] = Convert.ToUInt32(Temp);
                            }
                        }
                    }
                    break;

                case "LedConfig":
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
                    break;

                case "NetLEDConfig":
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
                    break;

                case "OPASLEDConfig":
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
                    break;

                case "Init":
                    try
                    {
                        GetRegValue("Led", ref RegValue);

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
                            Console.WriteLine("GetRegLed[{0}]={1:x}", i, GetRegLed[i]);
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
            catch (NullReferenceException)
            {
                Console.WriteLine("{0} are not create", UnitName);
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
                }
            }
        }
    }
}
