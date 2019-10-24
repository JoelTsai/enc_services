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
    static public class Program
    {
      public  static  EventLog pro_log = new EventLog();

        static void Main(string[] args)
        {
            if (args.Length != 0)
            {
                Enc_Service.TimeParameter = System.Text.RegularExpressions.Regex.Replace(args[0], "[^0-9]", "");
            }
            pro_log.Source = "MySource";
            if (!(Directory.Exists(Enc_Service.LogPath)))
            {
                Directory.CreateDirectory(Enc_Service.LogPath);
            }
            pro_log.WriteEntry("Hi hello world!");
            ServiceBase[] ServicesToRun;
            ServicesToRun = new ServiceBase[]
            {
                new Enc_Service()
            };
            ServiceBase.Run(ServicesToRun);
        }
    }
}
