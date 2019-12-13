using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Chip.Contrl
{
    static class NCT7802_Constants
    {

        //public const uint[,] NCT7802Y_ENV_CTRL_FAN_MATRIX = { NIDEC, SYSTEM_FAN , {0x0F,0x1F,0x2F,0x3F,0x4F,0x5F,0x6F,0x7F,0x8F,0x9F,0xAF,0xBF,0xCF,0xDF,0xEF,0xFE}};
        internal static readonly uint[] NIDEC_FAN_Level = { 0x0F, 0x1F, 0x2F, 0x3F, 0x4F, 0x5F, 0x6F, 0x7F, 0x8F, 0x9F, 0xAF, 0xBF, 0xCF, 0xDF, 0xEF, 0xFE };
        internal static readonly uint[] DELTA_FAN_Level = { 0x4F, 0x5F, 0x68, 0x6F, 0x78, 0x7F, 0x88, 0x8F, 0x98, 0x9F, 0xAF, 0xBF, 0xCF, 0xDF, 0xEF, 0xFF };

        internal const uint BLEN = 1;
        internal const uint WLEN = 2;
        internal const uint DWLEN = 4;


        internal const uint NCT7802Y_I2C_SUCCESS = 0;
        internal const uint NCT7802Y_I2C_FAILURE = 1;

        internal const uint NCT7802Y_PSU_LED_INIT = 0x0A;
        //internal const uint NCT7802Y_BP_HW_MONITOR_ADDR     = 0x2C;
        internal const uint NCT7802Y_BP_HW_MONITOR_ADDR = 0x2E;
        internal const uint NCT7802Y_BP_MID_PLANE_HW_MONITOR_ADDR = 0x28;

        internal const uint PCA955A_READ_PORT_0 = 0x00;
        internal const uint PCA955A_READ_PORT_1 = 0x01;
        internal const uint PCA955A_WRITE_PORT_0 = 0x02;
        internal const uint PCA955A_WRITE_PORT_1 = 0x03;
        internal const uint PCA955A_CONFIG_PORT_0 = 0x06;
        internal const uint PCA955A_CONFIG_PORT_1 = 0x07;

        //
        internal const uint NCT7802Y_PSU_INITIAL_FAN_SPEED_LEVEL = 8;

        internal const uint NCT7802Y_POWER_MID_PLANE_ADDR_1 = (0x54 >> 1);
        internal const uint NCT7802Y_POWER_MID_PLANE_ADDR_2 = (0x50 >> 1);
        internal const uint NCT7802Y_POWER_MID_PLANE_ADDR_3 = (0x56 >> 1);
        internal const uint NCT7802Y_POWER_MID_PLANE_ADDR_4 = (0x4C >> 1);

        internal const uint NCT7802Y_POWER_MID_PLANE_GPIO_W_1 = (0x72 >> 1);
        internal const uint NCT7802Y_POWER_MID_PLANE_GPIO_R_1 = (0x73 >> 1);
        internal const uint NCT7802Y_POWER_MID_PLANE_GPIO_W_2 = (0x74 >> 1);
        internal const uint NCT7802Y_POWER_MID_PLANE_GPIO_R_2 = (0x75 >> 1);


        /* ID */
        internal const uint NCT7802Y_SUPERIO_CHIP_ID_REG = 0xFE;

        /* BP VPD */
        internal const uint NCT7802Y_BP_VPD = 0x51;

        /* 1U4 */
        /* fan */
        internal const uint NCT7802Y_1U4_BP_DEVICE_FAN0 = 0x00;
        internal const uint NCT7802Y_1U4_BP_DEVICE_FAN1 = 0x01;
        internal const uint NCT7802Y_1U4_BP_DEVICE_FAN2 = 0x02;
        internal const uint NCT7802Y_1U4_BP_DEVICE_FAN3 = 0x03;
        internal const uint NCT7802Y_1U4_BP_DEVICE_FAN_ALL = 0xFF;

        internal const uint NCT7802Y_1U4_ENV_CTRL_FAN_SPEED_UNDER_MAX = 20000;
        internal const uint NCT7802Y_1U4_ENV_CTRL_FAN_MAX_LEVEL = 0xFE;
        internal const uint NCT7802Y_1U4_ENV_CTRL_FAN_SPIN_STABLE = 5;

        /* Device count */
        internal const uint NCT7802Y_1U4_BP_FAN_DEVICE_CNT = 0x04;

        /* 2U6 */
        /* fan */
        internal const uint NCT7802Y_2U6_BP_DEVICE_FAN0 = 0x00;
        internal const uint NCT7802Y_2U6_BP_DEVICE_FAN1 = 0x01;
        internal const uint NCT7802Y_2U6_BP_DEVICE_FAN_ALL = 0xFF;

        /* 2U8 */
        /* fan */
        internal const uint NCT7802Y_2U8_BP_DEVICE_FAN0 = 0x01;
        internal const uint NCT7802Y_2U8_BP_DEVICE_FAN1 = 0x02;
        internal const uint NCT7802Y_2U8_BP_DEVICE_FAN_ALL = 0xFF;

        /* fan fan control pin unplug */
        internal const uint NCT7802Y_2U6_ENV_CTRL_FAN_SPEED_UNDER_MAX = 7000;
        internal const uint NCT7802Y_2U6_ENV_CTRL_FAN_MAX_LEVEL = 0x7F;
        internal const uint NCT7802Y_2U6_ENV_CTRL_FAN_SPIN_STABLE = 5;
        //
        internal const uint NCT7802Y_2U8_ENV_CTRL_FAN_SPEED_UNDER_MAX = 10000;
        internal const uint NCT7802Y_2U8_ENV_CTRL_FAN_MAX_LEVEL = 0x7F;
        internal const uint NCT7802Y_2U8_ENV_CTRL_FAN_SPIN_STABLE = 5;



        /* Device count */
        internal const uint NCT7802Y_2U6_BP_FAN_DEVICE_CNT = 0x02;

        internal const uint NCT7802Y_PWR_BUTTON_NOPRESS = 0x01;
        internal const uint NCT7802Y_PWR_BUTTON_PRESS = 0x00;


        /* Configuration register */
        internal const uint NCT7802Y_CONFIG_RESET_REG = 0xFC;
        internal const uint NCT7802Y_CONFIG_RESET_DATA_STOP = 0x80;
        internal const uint NCT7802Y_CONFIG_START_REG = 0x21;
        internal const uint NCT7802Y_CONFIG_DATA_STOP = 0x00;
        internal const uint NCT7802Y_CONFIG_DATA_START = 0x01;

        /* Bank 0 */
        internal const uint NCT7802Y_BANK_SEL_REG = 0x00;
        internal const uint NCT7802Y_BANK_DATA_0 = 0;
        internal const uint NCT7802Y_BANK_DATA_1 = 1;

        /* GPIO */
        internal const uint NCT7802Y_GPIO_MODE_SELECT_REG = 0x22;
        internal const uint NCT7802Y_GPIO_FAN_ENABLE_REG = 0x24;
        internal const uint NCT7802Y_GPIO_ENABLE_REG = 0x55;
        internal const uint NCT7802Y_GPIO_MODE_SEL_REG = 0x56;
        internal const uint NCT7802Y_GPIO_OUTPUT_TYPE_REG = 0x57;
        internal const uint NCT7802Y_GPIO_INPUT_DATA_REG = 0x58;
        internal const uint NCT7802Y_GPIO_OUTPUT_DATA_REG = 0x59;
        internal const uint NCT7802Y_TEMP_DETECT_RATE = 0x26;
        internal const uint NCT7802Y_TEMP_FILTER_RATE = 0xCB;

        /* Voltage */
        internal const uint NCT7802Y_VOLT_ENABLE_REG = 0x25;
        internal const uint NCT7802Y_VOLT_VSEN1_H_REG = 0x0C;
        internal const uint NCT7802Y_VOLT_VSEN2_H_REG = 0x0D;
        internal const uint NCT7802Y_VOLT_VSEN3_H_REG = 0x0E;
        internal const uint NCT7802Y_VOLT_VCORE_H_REG = 0x0A;
        internal const uint NCT7802Y_VOLT_LOW_REG = 0x0F;
        internal const uint NCT7802Y_VOLT_VCC_REG = 0x09;

        /* Temperature */
        internal const uint NCT7802Y_TEMP_RTD2_HIGH_REG = 0x02;
        internal const uint NCT7802Y_TEMP_RTD3_HIGH_REG = 0x03;
        internal const uint NCT7802Y_TEMP_TR1_HIGH_REG = 0x01;
        internal const uint NCT7802Y_TEMP_TD2_REG = 0x02;
        internal const uint NCT7802Y_TEMP_TD_REG = 0x04;
        internal const uint NCT7802Y_TEMP_TD3_REG = 0x03;
        internal const uint NCT7802Y_TEMP_TD_LOW_REG = 0x05;
        internal const uint NCT7802Y_TEMP_TR2_OFFSET_REG = 0xC5;
        internal const uint NCT7802Y_TEMP_TR3_OFFSET_REG = 0xC6;

        /* Fan */
        internal const uint NCT7802Y_FAN_IN1_COUNT_REG = 0x10;
        internal const uint NCT7802Y_FAN_IN2_COUNT_REG = 0x11;
        internal const uint NCT7802Y_FAN_IN3_COUNT_REG = 0x12;
        internal const uint NCT7802Y_FAN_LOW_COUNT_REG = 0x13;
        internal const uint NCT7802Y_FAN_OUTPUT_TYPE_REG = 0x5E;
        internal const uint NCT7802Y_FAN_OUTPUT_MODE_REG = 0x5F;
        internal const uint NCT7802Y_FAN_FANCTL1_REG = 0x60;
        internal const uint NCT7802Y_FAN_FANCTL2_REG = 0x61;
        internal const uint NCT7802Y_FAN_FANCTL3_REG = 0x62;

        /* GPIO MASK */
        internal const uint NCT7802Y_GPIO1_MASK = 0x01;
        internal const uint NCT7802Y_GPIO2_MASK = 0x02;
        internal const uint NCT7802Y_GPIO3_MASK = 0x04;
        internal const uint NCT7802Y_GPIO4_MASK = 0x08;
        internal const uint NCT7802Y_GPIO5_MASK = 0x10;
        internal const uint NCT7802Y_GPIO6_MASK = 0x20;
        internal const uint NCT7802Y_GPIO7_MASK = 0x40;
        internal const uint NCT7802Y_GPIO8_MASK = 0x80;

        /* GPIO BIT */
        internal const uint NCT7802Y_GPIO_BIT_0 = 0;
        internal const uint NCT7802Y_GPIO_BIT_1 = 1;
        internal const uint NCT7802Y_GPIO_BIT_2 = 2;
        internal const uint NCT7802Y_GPIO_BIT_3 = 3;
        internal const uint NCT7802Y_GPIO_BIT_4 = 4;
        internal const uint NCT7802Y_GPIO_BIT_5 = 5;
        internal const uint NCT7802Y_GPIO_BIT_6 = 6;
        internal const uint NCT7802Y_GPIO_BIT_7 = 7;

        internal const uint SANYO = 0;
        internal const uint SUNON = 1;
        internal const uint REGO = 2;
        internal const uint NIDEC = 3;
        internal const uint DELTA = 4;

        internal const uint SYSTEM_FAN = 0;
        internal const uint CPU_FAN = 1;

        internal const uint NCT7802Y_MAX_FAN_MATRIX = 3;

    }//end of Constants

    static class CPU_IA32_Constants
    {
        internal const uint IA32_THERM_STATUS = 0x19C;
        internal const uint MSR_TEMPERATURE_TARGET = 0x1A2;
    }

    static class NCT5567_Constants
    {

        internal const uint NCT5567_ENV_CTRL_FAN_SEN_CPUTIN = 0;
        internal const uint NCT5567_ENV_CTRL_FAN_SEN_SYSTIN = 1;
        internal const uint NCT5567_ENV_CTRL_FAN_SEN_AUXTIN = 2;
        internal const uint NCT5567_ENV_CTRL_FAN_ALL = 0xFF;

        internal const uint NCT5567_ENV_FAN_CONFIG_SYSFAN_REG = 0x004;
        internal const uint NCT5567_ENV_FAN_CONFIG_FAN_PWM = 0x000;
        internal const uint NCT5567_ENV_FAN_MODE_SYSFAN_REG = 0x102;
        internal const uint NCT5567_ENV_FAN_MODE_CPUFAN_REG = 0x202;
        internal const uint NCT5567_ENV_FAN_MODE_AUXFAN_REG = 0x302;
        internal const uint NCT5567_ENV_FAN_MODE_AUXFAN2_REG = 0x902;
        internal const uint NCT5567_ENV_FAN_MODE_FAN_MANUAL_MODE = 0x000;
        internal const ushort NCT5567_ENV_FAN_SET_SYSFAN_REG = 0x109;
        internal const ushort NCT5567_ENV_FAN_SET_CPUFAN_REG = 0x209;
        internal const ushort NCT5567_ENV_FAN_SET_AUXFAN_REG = 0x309;
        internal const ushort NCT5567_ENV_FAN_SET_AUXFAN2_REG = 0x909;
        internal const ushort NCT5567_ENV_FAN_GET_SYSFAN_VAL_H_REG = 0x4C0;
        internal const ushort NCT5567_ENV_FAN_GET_SYSFAN_VAL_L_REG = 0x4C1;
        internal const ushort NCT5567_ENV_FAN_GET_CPUFAN_VAL_H_REG = 0x4C2;
        internal const ushort NCT5567_ENV_FAN_GET_CPUFAN_VAL_L_REG = 0x4C3;
        internal const ushort NCT5567_ENV_FAN_GET_AUXFAN_VAL_H_REG = 0x4C4;
        internal const ushort NCT5567_ENV_FAN_GET_AUXFAN_VAL_L_REG = 0x4C5;
        internal const ushort NCT5567_ENV_FAN_GET_AUXFAN2_VAL_H_REG = 0x4C8;
        internal const ushort NCT5567_ENV_FAN_GET_AUXFAN2_VAL_L_REG = 0x4C9;
        internal const ushort NCT5567_ENV_FAN_GET_SYSFAN_COUNT_H_REG = 0x4B0;
        internal const ushort NCT5567_ENV_FAN_GET_SYSFAN_COUNT_L_REG = 0x4B1;
        internal const ushort NCT5567_ENV_FAN_GET_CPUFAN_COUNT_H_REG = 0x4B2;
        internal const ushort NCT5567_ENV_FAN_GET_CPUFAN_COUNT_L_REG = 0x4B3;
        internal const ushort NCT5567_ENV_FAN_GET_AUXFAN_COUNT_H_REG = 0x4B4;
        internal const ushort NCT5567_ENV_FAN_GET_AUXFAN_COUNT_L_REG = 0x4B5;
        internal const ushort NCT5567_ENV_FAN_GET_AUXFAN2_COUNT_H_REG = 0x4B8;
        internal const ushort NCT5567_ENV_FAN_GET_AUXFAN2_COUNT_L_REG = 0x4B9;

        internal const uint NCT5567_ENV_VOLT_CONFIG_VBAT_ENABLE = 0x01;
        internal const uint NCT5567_ENV_VOLT_CONFIG_VBAT_REG = 0x05D;

        internal const uint SIO_R1_VCORE = 0x0;
        internal const uint SIO_R2_VCORE = 0x1;
        internal const uint SIO_R1_3VCC = 0x22;
        internal const uint SIO_R2_3VCCE = 0x22;

        /* Need to check
         * internal const uint NCT5567_ENV_VOLT_CPUCORE_REG = 0x480;
        internal const uint Nct6776_ENV_VOLT_12V_REG = 0x021;
        internal const uint Nct6776_ENV_VOLT_AVCC_REG = 0x022;
        internal const uint Nct6776_ENV_VOLT_3VCC_REG = 0x023;
        internal const uint Nct6776_ENV_VOLT_VIN1_REG = 0x024;
        internal const uint Nct6776_ENV_VOLT_5V_REG = 0x025;
        internal const uint Nct6776_ENV_VOLT_VIN3_REG = 0x026;
        */
        internal const uint NCT5567_ENV_VOLT_3VSB_REG = 0x487;
        internal const uint NCT5567_ENV_VOLT_VBAT_REG = 0x488;

        internal const byte NCT5567_DEV = 0x07;

        internal const uint NCT6XXX_PARALLEL_PORT_LDN = 0x01;
        internal const uint NCT6XXX_UART_A_LDN = 0x02;
        internal const uint NCT6XXX_UART_B_LDN = 0x03;
        internal const uint NCT6XXX_GPIO_LDN = 0x07;
        internal const uint NCT6XXX_PME_LDN = 0x04;
        internal const uint NCT6XXX_HW_MONITOR_LDN = 0x0B;
        internal const uint NCT6XXX_GPIO_WDT1_LDN = 0x08;
        internal const uint NCT6XXX_PARALLEL_VID_LDN = 0x0D;

        internal const uint NCT5567_ENV_CTRL_BASE_ADDR_REG = 0x60;

        internal static readonly uint[] FAN_Level = { 0x4A, 0x4F, 0x5A, 0x5F, 0x6A, 0x6F, 0x7A, 0x7F, 0x8F, 0x9F, 0xAF, 0xBF, 0xCF, 0xDF, 0xEF, 0xFF };


        internal const byte CHIP_ID_REGISTER = 0x20;
        internal const byte CHIP_REVISION_REGISTER = 0x21;
        internal const byte BASE_ADDRESS_REGISTER = 0x60;
    }

    static class TCA6416_Constants
    {
        public const uint BLEN = 1;
        public const uint WLEN = 2;
        public const uint DWLEN = 4;

        public const uint ENC_LED_OFF = 0x00;
        public const uint ENC_LED_GREEN = 0x01;
        public const uint ENC_LED_RED = 0x02;
        public const uint ENC_LED_AMBER = 0x03;
        public const uint ENC_LED_DARK = 0x80;

        public const uint TCA6416A_I2C_ADDR_LO = 0x20;
        public const uint TCA6416A_I2C_ADDR_HI = 0x21;

        public const uint TCA6416A_PORT_0 = 0;
        public const uint TCA6416A_PORT_1 = 1;

        public const uint TCA6416A_INPUT_PORT_0 = 0x0;
        public const uint TCA6416A_INPUT_PORT_1 = 0x1;
        public const uint TCA6416A_OUTPUT_PORT_0 = 0x2;
        public const uint TCA6416A_OUTPUT_PORT_1 = 0x3;
        public const uint TCA6416A_POLARITY_PORT_0 = 0x4;
        public const uint TCA6416A_POLARITY_PORT_1 = 0x5;
        public const uint TCA6416A_CONFIG_PORT_0 = 0x6;
        public const uint TCA6416A_CONFIG_PORT_1 = 0x7;

        public const uint TCA6416A_GPIO_IN = 1;
        public const uint TCA6416A_GPIO_OUT = 0;

        public const uint TCA6416A_GPIO_PIN_0 = 0;
        public const uint TCA6416A_GPIO_PIN_1 = 1;
        public const uint TCA6416A_GPIO_PIN_2 = 2;
        public const uint TCA6416A_GPIO_PIN_3 = 3;
        public const uint TCA6416A_GPIO_PIN_4 = 4;
        public const uint TCA6416A_GPIO_PIN_5 = 5;
        public const uint TCA6416A_GPIO_PIN_6 = 6;
        public const uint TCA6416A_GPIO_PIN_7 = 7;
        public const uint TCA6416A_GPIO_PIN_8 = 8;
        public const uint TCA6416A_GPIO_PIN_9 = 9;
        public const uint TCA6416A_GPIO_PIN_10 = 10;
        public const uint TCA6416A_GPIO_PIN_11 = 11;
        public const uint TCA6416A_GPIO_PIN_12 = 12;
        public const uint TCA6416A_GPIO_PIN_13 = 13;
        public const uint TCA6416A_GPIO_PIN_14 = 14;
        public const uint TCA6416A_GPIO_PIN_15 = 15;

        public const uint ENC_LED_HDD_0 = 0;
        public const uint ENC_LED_HDD_1 = 1;
        public const uint ENC_LED_HDD_2 = 2;
        public const uint ENC_LED_HDD_3 = 3;
        public const uint ENC_LED_HDD_4 = 4;
        public const uint ENC_LED_HDD_5 = 5;
        public const uint ENC_LED_HDD_6 = 6;
        public const uint ENC_LED_HDD_7 = 7;
        public const uint ENC_LED_HDD_8 = 8;
        public const uint ENC_LED_HDD_9 = 9;
        public const uint ENC_LED_HDD_10 = 10;
        public const uint ENC_LED_HDD_11 = 11;
        public const uint ENC_LED_HDD_12 = 12;
        public const uint ENC_LED_HDD_13 = 13;
        public const uint ENC_LED_HDD_14 = 14;
        public const uint ENC_LED_HDD_15 = 15;
        public const uint ENC_LED_HDD = 16;
        public const uint ENC_LED_POWER = 17;
        public const uint ENC_LED_OPAS = 18;
        public const uint ENC_LED_GLOBE_ERR = 19;
        public const uint ENC_LED_RAID = 20;
        public const uint ENC_LED_RECORD = 21;
        public const uint ENC_LED_FAN = 22;
        public const uint ENC_LED_BATTERY = 23;
        public const uint ENC_LED_DEBUG = 24;
        public const uint ENC_LED_PSU = 25;
        public const uint ENC_LED_ETH1 = 26;
        public const uint ENC_LED_ETH2 = 27;

        public static ushort[] LedRegisters = new ushort[] { 0x20, 0x21 };
        public const uint FW_REQUEST_PORT0_MASK = 0xB0;
        public const uint FW_REQUEST_PORT1_MASK = 0x00;
        public const uint NET_REQUEST_MASK = 0x3C;
        public const uint OPAS_REQUEST_MASK = 0x03;

    }//end of Constants

    static class PCH_Constants
    {

        internal const uint PCH_QUICK = 0x00;
        internal const uint PCH_BYTE = 0x04;
        internal const uint PCH_BYTE_DATA = 0x08;
        internal const uint PCH_WORD_DATA = 0x0C;
        internal const uint PCH_PROC_CALL = 0x10;
        internal const uint PCH_BLOCK_DATA = 0x14;
        internal const uint PCH_I2C_BLOCK_DATA = 0x18;
        internal const uint PCH_BLOCK_LAST = 0x34;
        internal const uint PCH_I2C_BLOCK_LAST = 0x38;
        internal const uint PCH_START = 0x40;
        internal const uint PCH_PEC_EN = 0x80;

        internal const uint PCH_SMBUS_ENABLE = 0x01;
        internal const uint PCH_SMBUS_SMI_EN = 0x02;
        internal const uint PCH_SMBUS_SSRESET = 0x08;

        internal const uint SMBHSTSTS_BYTE_DONE = 0x80;
        internal const uint SMBHSTSTS_INUSE_STS = 0x40;
        internal const uint SMBHSTSTS_SMBALERT_STS = 0x20;
        internal const uint SMBHSTSTS_FAILED = 0x10;
        internal const uint SMBHSTSTS_BUS_ERR = 0x08;
        internal const uint SMBHSTSTS_DEV_ERR = 0x04;
        internal const uint SMBHSTSTS_INTR = 0x02;
        internal const uint SMBHSTSTS_HOST_BUSY = 0x01;

        internal const uint I2C_SMBUS_READ = 1;
        internal const uint I2C_SMBUS_WRITE = 0;
        internal const uint I2C_ERROR_LIMIT = 3;

        internal const uint PCH200_LPC_DEVICE_NUMBER = 0x1f;
        internal const uint PCH200_LPC_FUNCTION_NUMBER = 0x00;
        internal const uint PCH200_SMBUS_FUNCTION_NUMBER_SKYLAKE = 0x04;
        internal const uint PCH200_SMB_BASE = 0x20;

        internal const uint PCH200_SMB_HOSTC = 0x40;


        internal const uint MAX_TIMEOUT = 100;
        internal const uint MAX_INUSED_TIMEOUT = 200;
        internal const uint MAX_BUSY_TIMEOUT = 100;


        internal const uint PCH200_I2C_BP_DEV_ADDR_VA3120 = 0x51;
        internal const uint PCH200_I2C_BP_DEV_ADDR_VA3340 = 0x55;
        internal const uint PCH200_I2C_BP_DEV_ADDR_VA8020 = 0x57;

        internal const uint PCH200_I2C_DEV_PSU_0 = 0;
        internal const uint PCH200_I2C_DEV_PSU_1 = 1;
        internal const uint PCH200_I2C_DEV_PSU_2 = 2;

    }

    class Constants
    {
    }
}
