/*---------------------------------------------------------------------------**
**          Filename    : HDD.cs                                             **
**          Description : Get HDDs info from FW driver functions             **
**          Created on  :2019/07/15                                          **
**          Created by  : Joel Tsai                                          **
**         (C)Copyright Promise Technology Inc., 2019                        **
**                    All Rights  Reserved.                                  **
**---------------------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using i2api;

namespace Chip.Contrl
{
    public class HDD
    {
        
        public HDD()
        {
            //init

        }

        public static void  PDtemp_update(ref uint?[] HDD_TEMP)
        {
           


              //  Console.WriteLine("enter PDtemp_update");
                pMicHddInfo_t[] HDDinfo = null;
                I2connection.GetHardDiskDriveInfo(ref HDDinfo);
                //Console.WriteLine("length={0}",HDD_TEMP.Length);
                for(int i=0;i<HDD_TEMP.Length;i++)
                {
                    HDD_TEMP[i] = 0;
                }
               try
                {
                  for (int i = 0; i < HDDinfo.Length; i++)
                   {
                    int slotid = Convert.ToInt32(HDDinfo[i].PDId);
                  // Console.WriteLine("slotid={0}", slotid);
                    //if (i == HDDinfo[0].NumOfPD)
                      //  break;

                    HDD_TEMP[slotid - 1] = Convert.ToUInt16(HDDinfo[i].temperature);

                  //  Console.WriteLine("NumOfPD[{1}]={0}", HDDinfo[i].NumOfPD, i);
                   // Console.WriteLine("PDId[{1}]={0}", HDDinfo[i].PDId, i);
                  //  Console.WriteLine("confCapacity[{1}]={0}", HDDinfo[i].confCapacity, i);
                  //  Console.WriteLine("temperature[{1}]={0}", Convert.ToUInt16(HDDinfo[i].temperature), i);

                  }
                }
                catch(Exception ex)
                {

                   // Prom_Enclosure_Serives.Log_File.FileLog(Convert.ToString(ex));
                }
        }

    }
}
