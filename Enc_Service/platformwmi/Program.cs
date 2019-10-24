//
using System;
using System.Collections.Generic;
using System.IO;
using Microsoft.Win32;
using System.Threading;
using System.Diagnostics;
using platformwmi.platformwmi;
using Enclsoure;
using System.Management;

namespace platformwmi
{

    class Program : IDisposable
    {
        private Enclsoure_class Enclosure;
        private Dictionary<string, uint?[]> AllData;


        public static bool process_flag = false;
        public uint?[] GetRegFan;// GetRegFan.Length = 4 * Fan.Length
        public uint?[] GetRegTemperature;// GetRegTemperature.Length = 4 * Temperature.Length
        public uint?[] GetRegVoltage;// GetRegVoltage.Length = 4 * Voltage.Length
        public uint?[] Temp_threshold;
        public uint?[,] GetRegLed;
        public Program()
        {
            this.Enclosure = new Enclsoure_class();

            RegistryKey localKey = null, softwareKey = null, key4Driver = null;
            try
            {
                localKey = RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.LocalMachine, RegistryView.Registry64);
                softwareKey = localKey.OpenSubKey("SOFTWARE", true);
                key4Driver = softwareKey.CreateSubKey("Pro_HWMonitor", RegistryKeyPermissionCheck.ReadWriteSubTree);
                if (key4Driver == null)
                    throw new Exception("Unable to create or open registry key");
            }
            finally
            {
                if (key4Driver != null) key4Driver.Close();
                if (softwareKey != null) softwareKey.Close();
                if (localKey != null) localKey.Close();
            }
        }

        public void Dispose()
        {
            this.Close();
        }

        public void Close()
        {
           /* if (this.computer != null)
            {
                Console.WriteLine("Dispose computer");
                this.computer.Close();
                this.computer = null;
            }
            else
            {*/
                Console.WriteLine("Computer has already been displosed.");
            //}
        }

        static void ShowHelp(NDesk.Options.OptionSet p)
        {
            Console.WriteLine("Usage: platformwmi.exe [OPTIONS]");
            Console.WriteLine();
            Console.WriteLine("Options:");
            p.WriteOptionDescriptions(Console.Out);
        }

        static int Main(string[] args)
        {
            bool show_help = false;
            int interval = -1; // This value will not be changed if no "-i" in args.



            //ManagementScope Scope = new ManagementScope("\\\\.\\root\\default");

            WqlEventQuery query = new WqlEventQuery(@"SELECT * FROM RegistryKeyChangeEvent WHERE Hive='HKEY_LOCAL_MACHINE' AND KeyPath='SOFTWARE\\Pro_HWMonitor'");
            ManagementEventWatcher watcher = new ManagementEventWatcher(query);


            try
            {
                DebugLogger.LoadConfiguration();
            }
            catch (Exception ex)
            {
                // Fail to check the debug option in registry. Just disable the debug logger.
                Console.WriteLine(ex.ToString());
                DebugLogger.Disable();
            }

            DebugLogger.WriteLine("==== START DebugLogger ====");

            var optionSet = new NDesk.Options.OptionSet() {
                { "i|interval=", 
                   "the time interval of updating, in seconds.\n" + "No loops if it is not a vaild positive integer",
                    (int v) => interval = (v<0?0:v) },
                { "h|help",  "show this message and exit", 
                   v => show_help = v != null },

            };

            List<string> extra = null;
            try
            {
                extra = optionSet.Parse(args);
            }
            catch (NDesk.Options.OptionException e)
            {
                Console.WriteLine(e.Message);
                Console.WriteLine("Try `platformwmi.exe --help' for more information.");
                return -1;
            }

            if (show_help)
            {
                ShowHelp(optionSet);
                return 0;
            }

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
                        return 0;
                    }
                }
            }


            using (Program program = new Program())/*init the chip.*/
                {

                /*do first request check*/
                //int stusa ;
                //I2bHddInfo_t i2HDDtest = new I2bHddInfo_t();
                watcher.EventArrived += new EventArrivedEventHandler(program.ChkReqRoutine);
                watcher.Start();
                do
                   {
                    Console.WriteLine("----------------------------v0.1");

                       program.Enclosure.GetEnclosureData(ref program.AllData);
                       program.SetToREG();


                        if(interval > 0)
                        Thread.Sleep(interval * 1000);
                        
                       
                    } while (interval >= 0) ;
                }
            process_flag = true;
            watcher.Stop();
            return 0;
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

            }
        }
        public void ChkReqRoutine(object sender, EventArrivedEventArgs e)
        {
            Console.WriteLine("reg Chang!!!");
            //bool request_flag = false;
            if (GetRegistry("FanConfig"))
            {
                Enclosure.Enclosure_SET_fan(GetRegFan);
                //request_flag = true;
            }
            if (GetRegistry("LedConfig"))
            {
                Enclosure.Enclosure_SET_led(GetRegLed);
               // request_flag = true;
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
         
            byte[] RegValue=null;

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
                            GetRegFan = new uint?[RegValue.Length/4];
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
                        if (!GetRegValue(unit, ref   RegValue))
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
                                        int Temp= RegValue[i + 2];
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
                            GetRegLed = new uint?[RegValue.Length / 4, 2];
                            for (int i = 0; i < RegValue.Length; i += 4)
                            {
                                if (i % 4 == 0)
                                {
                                    int ledreg = ((RegValue[i + 2]) | (RegValue[i] << 8));
                                    GetRegLed[(i / 4), 0] = (uint)(i / 4);
                                    GetRegLed[(i / 4), 1] = Convert.ToUInt32(ledreg);
                                    Console.WriteLine("i = [{0:x}]", i);
                                    Console.WriteLine("LedReg = [{0:x}]", ledreg);                                
                                }
                                //Console.WriteLine("{0}[{1}] = {2:x} ", UnitName, i + 1, GetRegVoltage[i]);
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
            try
            {
                RegistryKey localKey = null, softwareKey = null, key4Driver = null;

                localKey = RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.LocalMachine, RegistryView.Registry64);
                softwareKey = localKey.OpenSubKey("SOFTWARE", true);
                key4Driver = softwareKey.OpenSubKey("Pro_HWMonitor", RegistryKeyPermissionCheck.ReadWriteSubTree);

                byte[] ValueUnit = (byte[])key4Driver.GetValue(UnitName);


                RegValue = new byte[(ValueUnit[0] & 0x3F) * 4];
                //Console.WriteLine("Length=[{0}]", RegValue.Length);

                UInt32 FanFlag = (UInt32)(ValueUnit[0] & 0x80);
                if (FanFlag == 0)
                {
                    //Console.WriteLine("bool=[{0}]", ValueUnit[0]);
                    key4Driver.Close();
                    softwareKey.Close();
                    localKey.Close();
                    return false;
                }

                for (int i = 0; i < RegValue.Length; i++)
                {
                    RegValue[i] = ValueUnit[i + 4];
                }

                ValueUnit[0] = Convert.ToByte(Convert.ToInt16(ValueUnit[0]) & 0x7F);
                key4Driver.SetValue(UnitName, ValueUnit, RegistryValueKind.Binary);
                key4Driver.Close();
                softwareKey.Close();
                localKey.Close();
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine(" Cannot get reg {0},{1} ", UnitName,ex);
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
                                // foreach (string sensorValue in kv.Value)
                                for(int i=0;i<kv.Value.Length;i++)
                                {
                                  //  UInt32 result;
                                 /*   if (!UInt32.TryParse(sensorValue, out result))
                                    {
                                        result = 0;
                                    }*/
                                    writer.Write((UInt32)kv.Value[i]);
                                    //Console.WriteLine("value {0:x}", kv.Value[i]);
                                    //DebugLogger.WriteLine(string.Format("Fan 0x{0:X8} ({0})", result));
                                }

                                key4Driver.SetValue(kv.Key, buffer.ToArray(), RegistryValueKind.Binary);
                                //Console.WriteLine(BitConverter.ToString(buffer.ToArray()));
                                break;
                            case "Control":
                                break;
                            case "Voltage":
                                writer.Write((UInt32)kv.Value.Length);
                                //foreach (string sensorValue in kv.Value)
                                for (int i = 0; i < kv.Value.Length; i++)
                                {
                                    //byte result;
                                    /*if (!byte.TryParse(sensorValue, out result))
                                    {
                                        result = 0;
                                    }*/
                                    uint u32Voltage = VoltageToU32(Convert.ToByte(kv.Value[i]));
                                    writer.Write(u32Voltage);
                                    //DebugLogger.WriteLine(string.Format("Voltage 0x{0:X8}", u32Voltage));
                                }
                                //Console.WriteLine(BitConverter.ToString(buffer.ToArray()));
                                key4Driver.SetValue(kv.Key, buffer.ToArray(), RegistryValueKind.Binary);
                                break;
                            case "Temperature":
                                writer.Write((UInt32)kv.Value.Length);
                                //foreach (string sensorValue in kv.Value)
                                for (int i = 0; i < kv.Value.Length; i++)
                                {
                                    //UInt16 result;
                                   /* if (!UInt16.TryParse(sensorValue, out result))
                                    {
                                        result = 0;
                                    }*/
                                    writer.Write((UInt32)kv.Value[i]);
                                    //DebugLogger.WriteLine(string.Format("Temperature 0x{0:X8} ({0})", result));
                                }
                                //Console.WriteLine(BitConverter.ToString(buffer.ToArray()));
                                key4Driver.SetValue(kv.Key, buffer.ToArray(), RegistryValueKind.Binary);
                                break;
                            case "Led":
                                writer.Write((UInt32)kv.Value.Length);
                                // foreach (string sensorValue in kv.Value)
                                for (int i = 0; i < kv.Value.Length; i++)
                                {
                                    //  UInt32 result;
                                    /*   if (!UInt32.TryParse(sensorValue, out result))
                                       {
                                           result = 0;
                                       }*/
                                    writer.Write((UInt32)kv.Value[i]);
                                    //Console.WriteLine("LED Reg Start!! ");
                                    //Console.WriteLine("Ledvalue {0:x}", kv.Value[i]);
                                }

                                key4Driver.SetValue(kv.Key, buffer.ToArray(), RegistryValueKind.Binary);
                                //Console.WriteLine(BitConverter.ToString(buffer.ToArray()));
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
