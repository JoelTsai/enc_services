using System;
using System.ServiceProcess;
using System.IO;
using System.Diagnostics;

namespace Prom_Enclosure_Serives
{
    static public class Program
    {
        public  static  EventLog Pro_Event_viewer ;
        public static bool SUP_EVT = false;//does OS support event viewer flag
        static void Main(string[] args)
        {

            try
            {
                Pro_Event_viewer = new EventLog();
                Pro_Event_viewer.Source = "Promise";
                Console.WriteLine("Event_viewer  support");
                SUP_EVT = true;
            }
            catch (Exception)
            {
                Console.WriteLine("Event_viewer not support");
                SUP_EVT = false;
            }

         
  //          Pro_Event_viewer.Log = "Promise_event";
            if (!(Directory.Exists(Log_File.LogPath)))
            {
                Directory.CreateDirectory(Log_File.LogPath);
            }

            DirectoryInfo LogExist = new DirectoryInfo(Log_File.LogPath);
            FileInfo[] FileExist = LogExist.GetFiles(Log_File.LogName + "*");
            Log_File.LogId = (FileExist.Length - 1);

            for (int i = 0; i <= Log_File.LogId; i++)
            {
                Log_File.LogFile[i] = Convert.ToString(FileExist[i]);
            }

            try
            {
                Pro_Event_viewer.WriteEntry("project init!");
            }
            catch (Exception)
            {
                Console.WriteLine("Event_viewer not support");
                SUP_EVT = false;
            }

            if ((args.Length != 0) && args[0] == "debug")
            {
                Console.WriteLine("Debug mode on");
                Prom_EnclosureS once = new Prom_EnclosureS();
                if (args.Length > 2)

                { once.interval = Convert.ToInt32(System.Text.RegularExpressions.Regex.Replace(args[1], "[^0-9]", "")); }
                else
                { once.interval = 5; }
                
                Console.WriteLine("interval={0}", once.interval);
                once.Enclosure_Console_update();
                return;
            }


            else
            {
                if (args.Length != 0)
                {
                    Prom_EnclosureS.TimeParameter = System.Text.RegularExpressions.Regex.Replace(args[0], "[^0-9]", "");
                }
                Console.WriteLine(" Prom_EnclosureS.TimeParameter={0}", Prom_EnclosureS.TimeParameter);

                ServiceBase[] ServicesToRun;
                ServicesToRun = new ServiceBase[]
                {
                       new Prom_EnclosureS()
                };
				
                ServiceBase.Run(ServicesToRun);

            }

        }

    }
    static internal class Log_File
    {
        /// <summary>
        /// is there necessary???????????????
        /// </summary>
        internal static string windrive = Path.GetPathRoot(Environment.SystemDirectory);
        internal static string LogPath = windrive + @"\ProgramData\Promise\ServiceLog\";
        internal static string LogName = "WMIServiceLog";
        internal static string LogType = ".txt";
        internal static int LogId = 0;
        internal static string[] LogTime = new string[3];
        internal static string[] LogFile = new string[3];
        internal static string FilePath = LogPath + LogName + LogType;
        internal static string FilePathTime;
        internal static int LogSize = 50 * 1024 * 1024;//MB


        static internal void FileLog(string LogMessage)
        {
            try
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
                        writer.WriteLine($"{DateTime.Now.ToString("yyyyMMdd_hh:mm:ss")}" + " , " + LogMessage);
                        writer.Close();
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
            catch(Exception)
            {

            }
        }

        static internal void DelLogFile()
        {
            DirectoryInfo LogExist = new DirectoryInfo(LogPath);
            FileInfo[] FileExist = LogExist.GetFiles(LogName + "*");

            string DeleteFilePath = LogPath + Convert.ToString(FileExist[0]);

            File.Delete(DeleteFilePath);
        }

        static internal void CheckLogSize()
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
    }
}
