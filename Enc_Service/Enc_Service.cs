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

namespace Enc_Service
{
    public partial class Enc_Service : ServiceBase
    {
        private ManagementEventWatcher mgmtEvtWatcher;
        public EventLog EventLog;
        private System.Timers.Timer MyTimer;
        public Enclsoure_class Enclosure;
        public Dictionary<string, uint?[]> AllData;
        public uint?[] GetRegFan;// GetRegFan.Length = 4 * Fan.Length
        public uint?[] GetRegTemperature;// GetRegTemperature.Length = 4 * Temperature.Length
        public uint?[] GetRegVoltage;// GetRegVoltage.Length = 4 * Voltage.Length
        public uint?[,] GetRegLed;

        public uint?[] Temp_threshold;
        public static bool process_flag = false;

        public static string TimeParameter = "30";
        public static string LogPath = @"C:\ProgramData\Promise\ServiceLog\";
        public static string LogName = "WMIServiceLog";
        public static string LogType = ".txt";

        public static int LogId = 0;
        public static int LogSize = 50 * 1024 * 1024;

        public static string[] LogTime = new string[3];
        public static string[] LogFile = new string[3];
        public static string FilePath = LogPath + LogName + LogType;
        public static string FilePathTime;

        public Enc_Service()
        {
            Program.pro_log.WriteEntry("hello in there");
            InitializeComponent();

            this.Enclosure = new Enclsoure_class();
            EventLog = new EventLog();

            if (!EventLog.SourceExists("Enc_Service"))
            {
                EventLog.CreateEventSource("Enc_Service", "Enc_Log");
            }
            EventLog.Source = "Enc_Service";
            EventLog.Log = "Enc_Log";
        }

        protected override void OnStart(string[] args)
        {
            DirectoryInfo LogExist = new DirectoryInfo(LogPath);
            FileInfo[] FileExist = LogExist.GetFiles(LogName + "*");

            EventLog.WriteEntry("Enc_Service started...");
            EventLog.WriteEntry("TimeParameter= \"" + TimeParameter + "\"\n");
            //this.Enclosure = new Enclsoure_class();
            LogId = (FileExist.Length - 1);

            for (int i = 0; i <= LogId; i++)
            {
                LogFile[i] = Convert.ToString(FileExist[i]);
            }

            FileLog("Service is Start!");
            enc_Service = new Enc_Service();
            try
            {
                MyTimer = new System.Timers.Timer();
                MyTimer.Interval = Convert.ToInt32(TimeParameter) * 1000;
                MyTimer.Elapsed += new ElapsedEventHandler(MyTimer_Elapsed);
                MyTimer.Start();
            }
            catch (Exception e)
            {
                
            }
        }

        protected override void OnStop()
        {
            FileLog("Service is Stop!");
            try
            {
                Program.pro_log.WriteEntry("Enc_Service stopped...");
                EventLog.WriteEntry("Enc_Service stopped...");
            }
            catch (Exception e)
            {
                EventLog.WriteEntry("Stop Management Event Watcher failed...");
            }
        }

        private void MyTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            //enc_Service = new Enc_Service();
            Enc_Main();

            //Log Test Code
            for (int i = 0; i < 50; i++)
            {
                //FileLog("Log Test");
            }
        }

        static public void FileLog(string LogMessage)
        {
            DirectoryInfo LogExist = new DirectoryInfo(LogPath);
            FileInfo[] FileExist = LogExist.GetFiles(LogName + "*");
           
            if (FileExist.Length == 0)
            {
                LogId = FileExist.Length;
                LogTime[LogId] = DateTime.Now.ToString("_yyyyMMdd_hhmmss");
                LogFile[LogId] = LogName + LogTime[LogId] + LogType;
                FilePathTime = LogPath + LogFile[LogId];
                using (FileStream stream = new FileStream(FilePathTime, FileMode.Append))
                using (StreamWriter writer = new StreamWriter(stream))
                {
                    writer.WriteLine($"{DateTime.Now.ToString("yyyyMMdd_hh:mm:ss")}" + ", Log file is create!");
                }
            }
            else
            {
                FilePathTime = LogPath + LogFile[LogId];
                using (FileStream stream = new FileStream(FilePathTime, FileMode.Append))
                using (StreamWriter writer = new StreamWriter(stream))
                {
                    writer.WriteLine($"{DateTime.Now.ToString("yyyyMMdd_hh:mm:ss")}" + " , " + LogMessage);
                    if (FileExist.Length == 3)
                    {
                        DelLogFile();
                    }
                    CheckLogSize();
                    writer.Close();
                }
            }
        }

        static public void CheckLogSize()
        {
            FileInfo filesize = new FileInfo(FilePathTime);
            if (filesize.Length >= LogSize)
            {
                LogId += 1;
                if (LogId == 3)
                {
                    LogId = 0;
                }
                LogTime[LogId] = DateTime.Now.ToString("_yyyyMMdd_hhmmss");
                LogFile[LogId] = LogName + LogTime[LogId] + LogType;
                FilePathTime = LogPath + LogFile[LogId];
            }
        }

        static public void DelLogFile()
        {
            DirectoryInfo LogExist = new DirectoryInfo(LogPath);
            FileInfo[] FileExist = LogExist.GetFiles(LogName + "*");

            string DeleteFilePath = LogPath + Convert.ToString(FileExist[0]);

            File.Delete(DeleteFilePath);
        }

        public void Dispose()
        {
            this.Close();
        }

        public void Close()
        {
            Console.WriteLine("Computer has already been displosed.");
        }
        public Enc_Service enc_Service;
        public  void Enc_Main()
        {
            bool show_help = false;
            int interval = -1; // This value will not be changed if no "-i" in args.

            /*
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
            */
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
                    }
                }
            }

          //  using (Enc_Service enc_Service = new Enc_Service())/*init the chip.*/
           // {
                //watcher.EventArrived += new EventArrivedEventHandler(enc_Service.ChkReqRoutine);
                //watcher.Start();
                enc_Service.ChkReqRoutine();
                /*
                try
                {

                    WqlEventQuery query = new WqlEventQuery("SELECT * FROM RegistryKeyChangeEvent WHERE Hive='HKEY_LOCAL_MACHINE' AND KeyPath='SOFTWARE\\Pro_HWMonitor'");
                    ManagementEventWatcher watcher = new ManagementEventWatcher(query);

                    watcher.EventArrived += new EventArrivedEventHandler(enc_Service.ChkReqRoutine);
                    // Start listening for events.
                    FileLog("Start");
                    watcher.Start();
                    FileLog("Start End");
                    System.Threading.Thread.Sleep(100000000);

                    watcher.Stop();
                }
                catch (ManagementException WatcherErr)
                {
                    FileLog("An error occurred: " + WatcherErr.Message);
                }
                */
                do
                {
                    Console.WriteLine("----------------------------v0.1");

                    enc_Service.Enclosure.GetEnclosureData(ref enc_Service.AllData);
                    enc_Service.SetToREG();


                    if (interval > 0)
                        Thread.Sleep(interval * 1000);

                } while (interval >= 0);
           // }
            process_flag = true;
            //watcher.Stop();
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

        //public void ChkReqRoutine(object sender, EventArrivedEventArgs e)
        public bool ChkReqRoutine()
        {
            bool request_flag = false;

            if (GetRegistry("FanConfig"))
            {
                FileLog("Fan Chang!!!");
                for (int i = 0; i < GetRegFan.Length; i ++)
                { 
                    FileLog(Convert.ToString(GetRegFan[i]));
                }
                Enclosure.Enclosure_SET_fan(GetRegFan);
                FileLog("Fan out!!!");
                request_flag = true;
            }
            if (GetRegistry("LedConfig"))
            {
                Enclosure.Enclosure_SET_led(GetRegLed);
                request_flag = true;
            }
            if (GetRegistry("Temp_threshold"))
            {
                Enclosure.Enclosure_SET_Temp_threshold(Temp_threshold);
                request_flag = true;
            }
            return request_flag;
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
                                //Console.WriteLine("FanLevel = {01:x}  FanCount = {1:x} ", FanLevel, FanCount);
                                FileLog("FanLevel = " + FanLevel);
                                FileLog("FanCount = " + FanCount);
                                GetRegFan[i / 4] = Convert.ToUInt32(FanLevel);
                                //Console.WriteLine("FanLevel[{0}] = {1:x} ", (i / 4), GetRegFan[i / 4]);
                                FileLog("GetRegFan = " + GetRegFan[i / 4]);
                            }
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
                        }
                    }
                    break;
                case "Temp_threshold":
                    if (!GetRegValue(unit, ref RegValue))
                    {
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

                UInt32 FanFlag = (UInt32)(ValueUnit[0] & 0x80);
                if (FanFlag == 0)
                {
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
