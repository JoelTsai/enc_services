/*---------------------------------------------------------------------------**
**          Filename    : PSU.cs                                             **
**          Description : Contorl PSU module                                 **
**          Created on  :2019/12/12                                          **
**          Created by  : Joel Tsai                                          **
**         (C)Copyright Promise Technology Inc., 2019                        **
**                    All Rights  Reserved.                                  **
**---------------------------------------------------------------------------*/
using System;
using i2api;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Chip.Contrl
{
    public class PSU
    {
        private byte ENC_PSU_DEVICE_CNT = 0x03;
        private byte ENC_A3340R_PSU_DEFAULT_FAN_SPEED = 0xFF;
        public NCT7802 NCT7802_MID;
        public PSU()
        {
            uint data = 0, offset = 0;
            uint addr = NCT7802_Constants.NCT7802Y_BP_MID_PLANE_HW_MONITOR_ADDR;
            NCT7802_MID = new NCT7802();
            NCT7802_MID.Chip_init(NCT7802_Constants.NCT7802Y_BP_MID_PLANE_HW_MONITOR_ADDR);

            data = NCT7802_Constants.NCT7802Y_BANK_DATA_0;
            offset = NCT7802_Constants.NCT7802Y_BANK_DATA_0;
            if (I2C_write_value(addr, offset, ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
               //goto exit_error;
            }

            /* Diable monitoring operations */
            data = NCT7802_Constants.NCT7802Y_CONFIG_DATA_STOP;
            offset = NCT7802_Constants.NCT7802Y_CONFIG_START_REG;
            if (I2C_write_value(addr, offset, ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
               // goto exit_error;
            }

            data = 0x2A;
            offset = NCT7802_Constants.NCT7802Y_GPIO_MODE_SELECT_REG;
            if (I2C_write_value(addr, offset, ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
               // goto exit_error;
            }

            /* Enable GPIO 3,GPIO 4 */
            data = 0x0C;
            offset = NCT7802_Constants.NCT7802Y_GPIO_ENABLE_REG;
            if (I2C_write_value(addr, offset, ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
               // goto exit_error;
            }

            data = 0x00;
            offset = NCT7802_Constants.NCT7802Y_GPIO_MODE_SEL_REG;
            if (I2C_write_value(addr, offset, ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
               // goto exit_error;
            }

            data = NCT7802_Constants.NCT7802Y_CONFIG_DATA_START;
            offset = NCT7802_Constants.NCT7802Y_CONFIG_START_REG;
            if (I2C_write_value(addr, offset, ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
                //goto exit_error;
            }

            PSULEDinit();
            PSUFanSpeedInit();
        }

        private void PSULEDinit()
        {
            uint data = 0, addr = 0, offset = 0;


            data = NCT7802_Constants.NCT7802Y_PSU_LED_INIT;
            addr = NCT7802_Constants.NCT7802Y_POWER_MID_PLANE_ADDR_4;
            offset = NCT7802_Constants.PCA955A_WRITE_PORT_1;

            if (I2C_write_value(addr, offset,ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
            }
        }

        private void PSUFanSpeedInit()
        {
            uint data = 0, addr = 0, offset = 0, fanNum;


            for (fanNum = 0; fanNum < ENC_PSU_DEVICE_CNT; fanNum++)
            {
                    switch (fanNum)
                    {
                        case PCH_Constants.PCH200_I2C_DEV_PSU_0:
                            addr = NCT7802_Constants.NCT7802Y_POWER_MID_PLANE_ADDR_2;
                            offset = NCT7802_Constants.NCT7802Y_FAN_FANCTL2_REG;
                            break;
                        case PCH_Constants.PCH200_I2C_DEV_PSU_1:
                            addr = NCT7802_Constants.NCT7802Y_POWER_MID_PLANE_ADDR_2;
                            offset = NCT7802_Constants.NCT7802Y_FAN_FANCTL1_REG;
                            break;
                        default:
                            Console.WriteLine("PCH200 PSU fan number out of range.\n");
                            break;
                    }

                    data = ENC_A3340R_PSU_DEFAULT_FAN_SPEED;
                    if (I2C_write_value(addr, offset, ref data) == -1)
                    {
                     Console.WriteLine("PCH200 PSU I2C write fail.\n");
                    }

            }
        }

        public int I2C_write_value(uint addr, uint reg, ref uint data)
        {
            // return pch200_smbus_write(addr, reg, PCH_BYTE_DATA, data, BLEN);
            uint[] data_temp = { data };
            return PCHSMBUS.WriteSMB(addr, reg, NCT7802_Constants.BLEN, ref data_temp);
        }

        public int I2C_read_value(uint addr, uint reg, ref uint data)
        {

            //return pch200_smbus_read(addr, reg, PCH_BYTE_DATA, data, BLEN);
            int ret;
            uint[] data_temp = { data };
            ret = PCHSMBUS.ReadSMB(addr, reg, NCT7802_Constants.BLEN, ref data_temp);
            data = data_temp[0];
            return ret;

        }

    }
}
