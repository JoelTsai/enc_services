/*******************************************************************************
 * Filename    : mapi.h
 * Description : Main header file of MAPI
 *               
 * Created on  : 05/24/2005
 * CVS Version : $Id: mapi.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2005
 * All Rights Reserved
 ******************************************************************************/
 
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <crypt.h>
#include <stdarg.h>
#include <syslog.h>
#include <time.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

//#include <iconv.h>
#include "mapi_in.h"
#include "mapi_out.h"

#define DBG	0	

#define MAX_STR_LEN 256 
#define MAX_HT_VARIABLE 1024 
#define MAX_IDENT_LEN 16
//#define PASSWD "/etc/passwd"
//#define SHADOW "/etc/shadow"

#define HOMEDIR "/VOLUME1"

int htcount;

/* Get Function */
/* Perl Util File */


//LVM2 Perl
#define  PL_RECOVERSNAP          "/promise/util/recoversnap.pl"
#define  PL_DOSNAPSHOT           "/promise/util/dosnapshot.pl"
#define  PL_SETSNAPSHOT          "/promise/util/setsnapshot.pl"
#define  PL_SETDOMAIN            "/promise/util/setdomain.pl"
#define  PL_GETDOMAIN            "/promise/util/getdomain.pl"
#define  PL_GETSNAPLVINFO        "/promise/util/getsnaplv.pl"
#define  PL_SNAPSETUP            "/promise/util/getsnapsetup.pl"
#define  PL_SPMANAGER            "/promise/util/spmanager.pl"
#define  PL_VGMANAGER            "/promise/util/vgmanager.pl"
#define  PL_LVMANAGER            "/promise/util/lvmanager.pl"
#define  PL_PVMANAGER            "/promise/util/pvmanager.pl"
#define  PL_GETVGINFO            "/promise/util/getvginfo.pl"
#define  PL_GETPVINFO            "/promise/util/getpvinfo.pl"
#define  PL_GETLVINFO            "/promise/util/getlvinfo.pl"

#define  PL_SETLDNAME            "/promise/util/setldname.pl"
#define  PL_GETLDNAME            "/promise/util/getldname.pl"
#define  PL_ADJUSTDEV            "/promise/util/adjustdev.pl"
#define  PL_FORMAT               "/promise/util/format.pl"
#define  PL_MOUNTALL             "/promise/util/mountall.pl"
#define  PL_UMOUNTALL            "/promise/util/umountall.pl"
#define  PL_GETUSBDISK           "/promise/util/getstorinfo.pl"
#define  PL_USBFSINFO            "/promise/util/getusbfsinfo.pl"
#define  PL_GETESATA             "/promise/util/getesatainfo.pl"

#define  PL_WIZARD               "/promise/util/wizard.pl"
#define  PL_SYSINFO   		       "/promise/util/getsysinfo.pl"
#define  PL_PERFORMANCE 	       "/promise/util/getperformance.pl"
#define  PL_NETINFO   		       "/promise/util/getnetinfo.pl"
#define  PL_NETSETUP    	       "/promise/util/getnetsetup.pl"
#define  PL_DATE      		       "/promise/util/getdate.pl"
#define  PL_ENCINFO   		       "/promise/util/getencinfo.pl"
#define  PL_SMBCONFIG  		       "/promise/util/getsmbconfig.pl"
#define  PL_MAILLIST  		       "/promise/util/getmaillist.pl"
#define  PL_USER      		       "/promise/util/getuser.pl"
#define  PL_GROUP     		       "/promise/util/getgroup.pl"
#define  PL_QUOTAINFO 		       "/promise/util/getquotainfo.pl"
#define  PL_EVENTLOG  		       "/promise/util/geteventlog.pl"
#define  PL_FILESYSINFO 	       "/promise/util/getfilesysinfo.pl"
#define  PL_SHAREFOLDER 	       "/promise/util/getsharefolder.pl"
#define  PL_PROTOCOL  		       "/promise/util/getprotocol.pl"
#define  PL_GROUPMEMBER 	       "/promise/util/getgroupmember.pl"
#define  PL_NFSSHARE  		       "/promise/util/getnfsshare.pl"
#define  PL_PERMISSION  	       "/promise/util/getpermission.pl"
#define  PL_FTPPERMISSION  	     "/promise/util/getftppermission.pl"
#define  PL_NFSCOUNT       	     "/promise/util/getnfscount.pl"

#define  PL_PTRINFO              "/promise/util/getptrinfo.pl"
#define  PL_GETRSYNC             "/promise/util/getrsyncinfo.pl"
#define  PL_DORSYNC              "/promise/util/dorsync.pl"
#define  PL_SETRSYNC             "/promise/util/setrsync.pl"

#define  PL_SETRECYCLE           "/promise/util/setrecycle.pl"
#define  PL_SSLFTP               "/promise/util/sslftp.pl"

#define  PL_SETDLNA              "/promise/util/setdlna.pl"
#define  PL_SETMTU               "/promise/util/setmtu.pl"
#define  PL_SETLSPEED            "/promise/util/setlspeed.pl"

#define  PL_GETSMTP              "/promise/util/getsmtp.pl"
#define  PL_SETSMTP              "/promise/util/setsmtp.pl"

#define  PL_SETRSYNCD            "/promise/util/setrsyncd.pl"
#define  PL_NTPINFO              "/promise/util/getntpinfo.pl"
#define  PL_SETNTP               "/promise/util/setntp.pl"
#define  PL_UPSINFO              "/promise/util/getupsinfo.pl"
#define  PL_SETUPS               "/promise/util/setups.pl"
#define  PL_TIMEZONE             "/promise/util/gettimezone.pl"
#define  PL_SETTIMEZONE          "/promise/util/settimezone.pl"
#define  PL_SYNCTIME             "/promise/util/synctime.pl"
#define  PL_GETSCHEDULE       	 "/promise/util/getschedule.pl"
#define  PL_SETSCHEDULE       	 "/promise/util/setschedule.pl"

#define  PL_GETONETOUCH       	 "/promise/util/getonetouch.pl"
#define  PL_SETONETOUCH       	 "/promise/util/setonetouch.pl"

#define  PL_GETPOWER       	     "/promise/util/getpower.pl"
#define  PL_SETPOWER       	     "/promise/util/setpower.pl"

#define  PL_EXTENDFS             "/promise/util/extendfs.pl"
#define  PL_FORMATUSBHD          "/promise/util/formatusbhd.pl"

#define  PL_GETMOUNTINFO         "/promise/util/getmountinfo.pl"
#define  PL_INITRAID             "/promise/util/initraid.pl"
#define  PL_DELRAID              "/promise/util/delraid.pl"
#define  PL_MFORMAT              "/promise/util/mformat.pl"
#define  PL_MEXTENDFS            "/promise/util/mextendfs.pl"
#define  PL_RESCANDEV            "/promise/util/rescandev.pl"

#define  PL_GETSNAPLIST          "/promise/util/getsnaplist.pl"
#define  PL_EXPORTSNAP           "/promise/util/exportsnap.pl"

#define  PL_GETAUTHMODE       	 "/promise/util/getauthmode.pl"
#define  PL_SETAUTHMODE       	 "/promise/util/setauthmode.pl"
#define  PL_CHGGROUP          	 "/promise/util/chggroup.pl"

/* Perl Util File */
#define  PL_SETDATE		           "/promise/util/setdate.pl"
#define  PL_SETNETSETUP 	       "/promise/util/setnetsetup.pl"
#define  PL_SETMAILLIST 	       "/promise/util/setmaillist.pl"
#define  PL_SETHOSTNAME 	       "/promise/util/sethostname.pl"
#define  PL_SETDNS 		           "/promise/util/setdns.pl"
#define  PL_DELGROUPMEMBER 	     "/promise/util/delgroupmember.pl"
#define  PL_ADDSHAREFOLDER 	     "/promise/util/addsharefolder.pl"
#define  PL_DELSHAREFOLDER 	     "/promise/util/delsharefolder.pl"
#define  PL_SETQUOTA       	     "/promise/util/setquota.pl"
#define  PL_DELGROUOP 	 	       "/promise/util/delgroup.pl"
#define  PL_SETSMB		           "/promise/util/setsmb.pl"
#define  PL_SETNFS		           "/promise/util/setnfs.pl"
#define  PL_SETAFP		           "/promise/util/setafp.pl"
#define  PL_SETFTP         	     "/promise/util/setftp.pl"
#define  PL_SETPTR         	     "/promise/util/setprinter.pl"
#define  PL_SETPERMISSION  	     "/promise/util/setpermission.pl"
#define  PL_SETFTPPERMISSION     "/promise/util/setftppermission.pl"
#define  PL_DELUSER         	   "/promise/util/deluser.pl"
#define  PL_CHECKRAID      	     "/promise/util/checkraid.pl"
#define  PL_SETSMBCONFIG   	     "/promise/util/setsmbconfig.pl"
#define  PL_UPGRADE        	     "/promise/util/upgrade.pl"
#define  PL_SETNETSETUP          "/promise/util/setnetsetup.pl"
#define  PL_CHKDEADDEV           "/promise/util/chkdeaddev.pl"

#define  PL_PLUGIN               "/promise/util/plugin.pl"
#define  PL_RECOVERCONF          "/promise/util/recoverconfig.pl"
#define  PL_SETAPP               "/promise/util/setapp.pl"

#define  PL_SETAFPCONFIG   	     "/promise/util/setafpconf.pl"
#define  PL_GETAFPCONFIG   	     "/promise/util/getafpconf.pl"

#define  PL_SENDMAIL   	         "/promise/util/sendmail.pl"
#define  PL_CHECKFS   	         "/promise/util/chkfs.pl"
#define  PL_GETCHECKFSRES   	   "/promise/util/getchkfsres.pl"

/* Corega Project */
#define  PL_GETDDNS              "/promise/util/getddns.pl"
#define  PL_SETDDNS              "/promise/util/setddns.pl"
#define  RS_DDNS                 "/tmp/ddns.tmp"

#define  PL_GETFTPCONFIG         "/promise/util/getftpconfig.pl"
#define  PL_SETFTPCONFIG         "/promise/util/setftpconfig.pl"
#define  RS_FTP                  "/tmp/proftpd.tmp"

#define  PL_BACKUPCONFIG         "/promise/util/backupconfig.pl"
#define  PL_RESTORECONFIG        "/promise/util/restoreconfig.pl"
#define  PL_UMOUNTUSBDEV         "/promise/util/umountusbdev.pl"
#define  RS_RESTORETMP           "/tmp/restore.tmp"

#define  PL_SETPWM               "/promise/util/setpwm.pl"
#define  PL_SETWOL               "/promise/util/setwol.pl"

#define  PL_SETDST               "/promise/util/setdst.pl"

#define  PL_GETPLUGINAPP         "/promise/util/getpluginapp.pl"
#define  PL_SETPLUGINAPP         "/etc/init.d/pluginapp"
#define  PL_DELPLUGINAPP         "/promise/util/delplugin.pl"

#define  PL_GETFORMATPROG         "/promise/util/getformatprog.pl"
#define  PL_GETONLINEUSER         "/promise/util/getonlineuser.pl"
#define  PL_CHKHOMEDIR            "/promise/util/chkhomedir.pl"

#define  PL_NAVIWIZARD         		"/promise/util/c_wizard.pl"
#define  PL_IMPC            			"/promise/util/impc.pl"

#define  PL_AUTOPOWER             "/promise/util/autopower.pl"
#define  PL_GETLDINFO							"/promise/util/getldinfo.pl" //for vessRAID test
#define  PL_DISLD                 "/promise/util/disld.pl" //for vessRAID
#define  PL_FILEMGT		           "/promise/util/filemgt.pl"
#define  PL_CHANGEVOL		       "/promise/util/chgvolname.pl"
#define  PL_IPINFO		       "/promise/util/getipinfo.pl"
/* Result File */
#define  RS_RSYNCBUSY            "/tmp/rsyncbusy"
#define  RS_SYSBUSY              "/tmp/sysbusy"
#define  RS_GETRSYNC             "/tmp/rsyncinfo"
#define  RS_PTRINFO              "/tmp/ptrinfo"
#define  RS_SNAPSETUP            "/tmp/snapsetup"
#define  RS_DOMAIN               "/tmp/domaininfo"
#define  RS_SNAPINFO             "/tmp/snapinfo"
#define  RS_VGINFO               "/tmp/vginfo"
#define  RS_LVINFO               "/tmp/lvinfo"
#define  RS_PVINFO               "/tmp/pvinfo"
#define  RS_SYSINFO   	         "/tmp/sysinfo"
#define  RS_PERFORMANCE          "/tmp/performance"
#define  RS_NETINFO   	         "/tmp/netinfo"
#define  RS_NETSETUP   	         "/tmp/netsetup"
#define  RS_DATE      	         "/tmp/date"
#define  RS_ENCINFO   	         "/tmp/encinfo"
#define  RS_SMBCONFIG  	         "/tmp/smbconfig"
#define  RS_MAILLIST  	         "/tmp/maillist"
#define  RS_USER      	         "/tmp/user"
#define  RS_GROUP     	         "/tmp/group"
#define  RS_QUOTAINFO 	         "/tmp/quotainfo"
#define  RS_EVENTLOG  	         "/tmp/eventlog"
#define  RS_FILESYSINFO          "/tmp/filesysinfo"
#define  RS_SHAREFOLDER          "/tmp/sharefolder"
#define  RS_PROTOCOL  	         "/tmp/protocol"
#define  RS_GROUPMEMBER          "/tmp/groupmember"
#define  RS_NFSSHARE  	         "/tmp/nfsshare"
#define  RS_PERMISSION           "/tmp/permission"
#define  RS_BUZZER               "/tmp/buzzer.conf"
#define  RS_RESULT               "/tmp/result"
#define  RS_SMBCONFTMP           "/tmp/smbconf.tmp"
#define  RS_UPGRADETMP           "/tmp/upgrade.tmp"
#define  RS_PLUGINTMP            "/tmp/plugin.tmp"
#define  RS_PLUGINBUSY           "/tmp/pluginbusy"
#define  RS_PLUGINRESULT         "/tmp/pluginresult"
                                 
#define  RS_NTPINFO              "/tmp/ntpinfo"
#define  RS_UPSINFO              "/tmp/upsinfo"
#define  RS_TIMEZONE             "/tmp/timezone"
#define  RS_GETSCHEDULE          "/tmp/schedule"
#define  RS_LDNAME   	           "/tmp/ldname"
#define  RS_WIZARDTMP            "/tmp/wizard.tmp"
#define  RS_USBDISK              "/tmp/storinfo"
#define  RS_USBFSINFO            "/tmp/usbfsinfo"
#define  RS_ESATA                "/tmp/esatainfo"

#define  RS_ONETOUCH             "/tmp/onetouch"
#define  RS_USBBUSY              "/tmp/usbbusy"
#define  RS_USBRESULT            "/tmp/usbresult"

#define  RS_MOUNTINFO            "/tmp/mountinfo"
#define  RS_FORMATSTATUS         "/tmp/formating"
#define  RS_AUTHMODE             "/tmp/authmode"

#define  RS_SNAPLIST             "/tmp/snaplist"

#define  RS_SMTP                 "/tmp/smtp.tmp"
#define  RS_PLUGINAPP            "/tmp/pluginapp"

#define  RS_ONLINEUSER           "/tmp/onlineuser"
#define  RS_PROGRESS             "/tmp/progress"

#define  RS_RECYCLE              "/tmp/recycle.tmp"

#define  RS_POWER                "/tmp/power.tmp"

#define  RS_CHKFSRES             "/tmp/fsresult"
#define  RS_AFPCONF              "/tmp/afp.tmp"

#define  LOCATE                  "/usr/sbin/locate"

#define  RS_AUTOPOWER            "/tmp/autopower"

#define	 RESETCFG								 "/usr/sbin/resetcfg"
#define  RS_SMBPASSWD		"/tmp/smbpass"
#define  RS_LDINFO							"/tmp/ldinfo" //for VessRAID test
#define  RS_FILEMGT           	 "/tmp/filemgt.result"
#define  RS_IPINFO          "/tmp/ipinfo"

/* auth */
int check_auth(char *user,char *passwd);
int update_passwd(char *user, char *passwd);
char *get_passwd(const char *user);
char *encrypt_passwd(const char *clear, const char *salt);
	
/* mapi_util */
int is_exist ( char *filename );
void trim ( char* str );
void split ( char* str, char ch, char* token1 , char* token2 );
void readFile ( char *file );
char * getValue ( char *name);
void getToken(char *getval,char *token,int index);
int delFile(char *pathname);
void writeLog(char *identity, int facility, int level, char *message);
char * big5(char *ptr);

int  valid(char *pass);
//int  valid(char *pass);
int  etuserid(char* str);
void set(char **var,char *val);
int convert(char *,char *,char *,int *,char *,int *);

/* mapi */
int mapiRecoverSnap(input_setsnaplv_t * ptrparam);
int mapiSetLDname(input_setldname_t * ptrparam);
int mapiGetLDname(output_hp_getldname_t * ptrhead);
int mapiCheckResult(output_hp_netinfo_t * ptrhead);

int mapiWizUserheader();
int mapiWizSaveuser(char *,char *,char *);
int mapiWizSaveadminpwd(char *);
int mapiWizFolderheader();
int mapiWizSavefolder(char *);
int mapiWizSavesvc(char *,char *,char *,char *);
int mapiWizSavenet(char *,char *,char *);
int mapiWizExecute(char *);

int mapiAdjustdev();
int mapiFormat();
int mapiUmountall();

int mapiGetPtrinfo(output_hp_getptrinfo_t * ptrhead);
int mapiGetRsync(output_hp_getrsync_t * ptrhead);
int mapiSetRsync(input_setrsync_t * ptrparam);
int mapiDoRsync();

int mapiSetDomain(input_setdomain_t * ptrparam);
int mapiGetDomain(output_hp_getdomain_t * ptrhead);
int mapiCreateVG(input_setvg_t * ptrparam,output_hp_getvg_t * ptrhead);

int mapiSetSnapshot(input_snapshot_t * ptrparam);
int mapiDoSnapshot(input_snapshot_t * ptrparam);

int mapiGetSnapset(input_setsnaplv_t * ptrparam,output_hp_snapset_t * ptrhead);
int mapiGetsnapLVinfo(input_setsnaplv_t * ptrparam,output_hp_getsnaplv_t * ptrhead);
int mapiCreatesnapLV(input_setsnaplv_t * ptrparam,output_hp_getsnaplv_t * ptrhead);
int mapiRemoveVG(input_setvg_t * ptrparam,output_hp_getvg_t * ptrhead);
int mapiRemoveLV(input_setlv_t * ptrparam,output_hp_getlv_t * ptrhead);
int mapiCreateLV(input_setlv_t * ptrparam,output_hp_getlv_t * ptrhead);
int mapiRemovePV(input_setpv_t * ptrparam,output_hp_getpv_t * ptrhead);
int mapiCreatePV(input_setpv_t * ptrparam,output_hp_getpv_t * ptrhead);
int mapiGetVGinfo(output_hp_getvg_t * ptrhead);
int mapiGetLVinfo(output_hp_getlv_t * ptrhead);
int mapiGetPVinfo(output_hp_getpv_t * ptrhead);
int mapiGetSchedule(output_hp_schedule_t * ptrhead);
int mapiSetSchedule(input_schedule_t * ptrparam);
int mapiSetTimezone(input_timezone_t * ptrparam);
int mapiGetTimezone(output_hp_timezone_t * ptrhead);
int mapiGetNtpinfo(output_hp_ntpinfo_t * ptrhead);
int mapiSetNtp(input_ntp_t * ptrhead);
int mapiGetUpsinfo(output_hp_upsinfo_t * ptrhead);
int mapiSetUps(input_ups_t * ptrparam);
int mapiSyncTime();

int mapiGetSysinfo(output_hp_sysinfo_t * ptrhead);
int mapiGetNetinfo(output_hp_netinfo_t * ptrhead);
int mapiGetNetsetup(output_hp_netinfo_t * ptrhead);
int mapiGetEncinfo(output_hp_encinfo_t * ptrhead);
int mapiGetDate(output_hp_date_t * ptrhead);    
int mapiGetMaillist(output_hp_maillist_t * ptrhead);
int mapiGetGroup(output_hp_usergroup_t * ptrhead); 
int mapiGetUser(output_hp_usergroup_t * ptrhead);
int mapiGetSharefolder(output_hp_sharefolder_t * ptrhead);
int mapiGetProtocol(output_hp_protocol_t * ptrhead);  
int mapiGetFilesysinfo(output_hp_filesystem_t * ptrhead);
int mapiGetEventlog(output_hp_eventlog_t * ptrhead);
int mapiGetSMBconfig(output_hp_smbconfig_t * ptrhead);
int mapiGetPerformance(output_hp_performance_t * ptrhead);
int mapiGetGroupmember(input_usergroup_t * ptrparam, output_hp_groupmember_t * ptrhead);
int mapiGetNFSshare (input_sharefolder_t * ptrparam, output_hp_nfsshare_t * ptrhead);
int mapiGetPermission (input_sharefolder_t * ptrparam, output_hp_permission_t * ptrhead);
int mapiGetQuotainfo(input_quota_t * ptrparam, output_hp_quotainfo_t * ptrhead);
int mapiGetNFScount(output_hp_nfsshare_t * ptrhead); 
int mapiGetESATA(output_hp_usbdisk_t * ptrhead); 
int mapiGetUSBdisk(output_hp_usbdisk_t * ptrhead); 
int mapiGetOnetouch(output_hp_onetouch_t * ptrhead);
int mapiChecksysbusy();
int mapiCheckrsyncbusy();
int mapiWriteLog (input_log_t * ptrparam);
int mapiGetUIlanguage (output_hp_uilanguage_t * ptrhead);
int mapiGetBuzzer ();
int mapiSutdown();
int mapiReboot();
int mapiEnableBuzzer();
int mapiDisableBuzzer();
int mapiSetDate (input_date_t * ptrparam);
int mapiAddMaillist (input_maillist_t * ptrparam);
int mapiDelMaillist (input_maillist_t * ptrparam);
int mapiSetHostname (input_network_t * ptrparam);
int mapiSetDNS (input_network_t * ptrparam);
int mapiAddGroup (input_usergroup_t * ptrparam);
int mapiDelGroup (input_usergroup_t * ptrparam);
int mapiAddGroupmember (input_usergroup_t * ptrparam);
int mapiDelGroupmember (input_usergroup_t * ptrparam);
int mapiAddSharefolder (input_sharefolder_t * ptrparam);
int mapiDelSharefolder (input_sharefolder_t * ptrparam);
int mapiSetQuota (input_quota_t * ptrparam);
int mapiAddShareprotocol (input_sharefolder_t * ptrparam);
int mapiDelShareprotocol (input_sharefolder_t * ptrparam);
int mapiStartProtocol (input_sharefolder_t * ptrparam);
int mapiStopProtocol (input_sharefolder_t * ptrparam);
int mapiSetPermission (input_sharing_t * ptrparam);
int mapiAddUser (input_usergroup_t * ptrparam);
int mapiDelUser (input_usergroup_t * ptrparam);
int mapiSetPasswd (input_usergroup_t * ptrparam);
int mapiAddNFSshare (input_sharing_t * ptrparam);
int mapiDelNFSshare (input_sharing_t * ptrparam);
int mapiSetUIlanguage(input_uilanguage_t * ptrparam);
int mapiCheckRAID (input_sharefolder_t * ptrparam);
int mapiLogin (input_usergroup_t * ptrparam);
int mapiSetSMBconfig (input_smbconfig_t * ptrparam);
int mapiSetNetsetup (input_network_t * ptrparam,output_hp_netinfo_t * ptrhead);

int mapiSetMTU(input_network_t * ptrparam);
int mapiSetLspeed(input_network_t * ptrparam);

int mapiSetOnetouch(input_onetouch_t * ptrparam);
int mapiSetOnetouch_U(input_onetouch_t * ptrparam);

int mapiExtendfs();
int mapiFormatusbhd(input_usbhd_t * ptrparam);
int mapiCheckUSBResult();

int mapiUpgrade (input_upgrade_t * ptrparam);
int mapiUpgradeflash (input_upgrade_t * ptrparam);
int mapiUpgradeResult();

int mapiGetMountinfo(output_hp_mountinfo_t * ptrhead);
int mapiCheckFormatstatus(output_hp_mountinfo_t * ptrhead);
int mapiInitraid(input_raid_t * ptrparam);
int mapiDelraid(input_raid_t * ptrparam);
int mapiMformat(input_raid_t * ptrparam);
int mapiMextendfs(input_raid_t * ptrparam);
int mapiGetUsbfsinfo(output_hp_filesystem_t * ptrhead);
int mapiRescandev();

int mapiGetSnaplist(output_hp_snaplist_t * ptrhead);
int mapiExportSnap (input_setsnaplv_t * ptrparam);

int mapiGetAuthmode();
int mapiSetAuthmode(input_auth_t * ptrparam);
int mapiCheckDeaddev();

int mapiPlugin (input_upgrade_t * ptrparam);
int mapiPluginResult();
int mapiRecoverconfig(input_raid_t * ptrparam);

int mapiGetSMTP(output_hp_smtp_t * ptrhead);    
int mapiSetSMTP(input_smtp_t * ptrparam);

/* Corega Project */
int mapiGetDDNS(output_hp_ddns_t * ptrhead);
int mapiSetDDNS(input_ddns_t * ptrparam);
int mapiFreeDDNS(output_hp_ddns_t * ptrhead);

int mapiGetFTPconfig(output_hp_ftp_t * ptrhead);
int mapiSetFTPconfig(input_ftp_t * ptrparam);
int mapiFreeFTPconfig(output_hp_ftp_t * ptrhead);

int mapiRestoreconfig (input_upgrade_t * ptrparam);
int mapiBackupconfig(input_upgrade_t * ptrparam);
int mapiUmountusbdev();

int mapiSetpwm(input_protoctl_t * ptrparam);

int mapiSetDST(input_timezone_t * ptrparam);

int mapiGetPluginapp(output_hp_protocol_t * ptrhead);
int mapiStartApp (input_sharefolder_t * ptrparam);
int mapiStopApp (input_sharefolder_t * ptrparam);

int mapiGetFormatprog();
int mapiGetOnlineuser(output_hp_onlineuser_t * ptrhead);

int mapiEnableRecycle();
int mapiDisableRecycle();
int mapiGetRecycle();

int mapiImpc(input_command_t * ptrparam);
int mapiNaviWizard(input_command_t * ptrparam);

int mapiGetPower(output_hp_schedule_t * ptrhead);
int mapiSetPower(input_schedule_t * ptrparam);

int mapiSendMail();
int mapiSetAFPconfig (input_smbconfig_t * ptrparam);
int mapiGetAFPconfig(output_hp_smbconfig_t * ptrhead);
int mapiCheckFilesystem();
int mapiGetCheckfsres(output_hp_smbconfig_t * ptrhead);

int mapiEnableWOL();
int mapiDisableWOL();

int mapiEnableSSLFTP();
int mapiDisableSSLFTP();

int mapiGetAutopower();
int mapiEnableAutopower();
int mapiDisableAutopower();

/* mapi Free */ 
int mapiFreePtrinfo(output_hp_getptrinfo_t * ptrhead);
int mapiFreeGetRsync(output_hp_getrsync_t * ptrhead);
int mapiFreeDomain(output_hp_getdomain_t * ptrhead);
int mapiFreeVGinfo(output_hp_getvg_t * ptrhead);
int mapiFreesnapLVinfo(output_hp_getsnaplv_t * ptrhead);
int mapiFreeLVinfo(output_hp_getlv_t * ptrhead);
int mapiFreePVinfo(output_hp_getpv_t * ptrhead);
int mapiFreeSysinfo(output_hp_sysinfo_t * ptrhead);
int mapiFreeNetinfo(output_hp_netinfo_t * ptrhead);
int mapiFreeNetsetup(output_hp_netinfo_t * ptrhead);
int mapiFreeEncinfo(output_hp_encinfo_t * ptrhead);
int mapiFreeDate(output_hp_date_t * ptrhead);    
int mapiFreeMaillist(output_hp_maillist_t * ptrhead);
int mapiFreeGroup(output_hp_usergroup_t * ptrhead); 
int mapiFreeUser(output_hp_usergroup_t * ptrhead);
int mapiFreeQuotainfo(output_hp_quotainfo_t * ptrhead);
int mapiFreeSharefolder(output_hp_sharefolder_t * ptrhead);
int mapiFreeProtocol(output_hp_protocol_t * ptrhead);  
int mapiFreeFilesysinfo(output_hp_filesystem_t * ptrhead);
int mapiFreeEventlog(output_hp_eventlog_t * ptrhead);
int mapiFreeSMBconfig(output_hp_smbconfig_t * ptrhead);
int mapiFreePerformance(output_hp_performance_t * ptrhead);
int mapiFreeGroupmember(output_hp_groupmember_t * ptrhead);
int mapiFreeNFSshare (output_hp_nfsshare_t * ptrhead);
int mapiFreePermission (output_hp_permission_t * ptrhead);
int mapiFreeUserGroup(output_hp_usergroup_t * ptrhead);
int mapiFreeUIlanguage(output_hp_uilanguage_t * ptrhead);
int mapiFreeNtpinfo(output_hp_ntpinfo_t * ptrhead);
int mapiFreeTimezone(output_hp_timezone_t * ptrhead);
int mapiFreeUpsinfo(output_hp_upsinfo_t * ptrhead);
int mapiFreeSchedule(output_hp_schedule_t * ptrhead);
int mapiFreeLDname(output_hp_getldname_t * ptrhead);
int mapiFreeSnapset(output_hp_snapset_t * ptrhead);
int mapiFreeUSBdisk(output_hp_usbdisk_t * ptrhead);
int mapiFreeOnetouch(output_hp_onetouch_t * ptrhead);
int mapiFreeMountinfo(output_hp_mountinfo_t * ptrhead);
int mapiFreeSnaplist(output_hp_snaplist_t * ptrhead);
int mapiFreeSMTP(output_hp_smtp_t * ptrhead);
int mapiFreeOnlineuser(output_hp_onlineuser_t * ptrhead);
int mapiResetCfg();
int mapiGetLDinfo(output_hp_mountinfo_t * ptrhead); //add by VessRAID develop
u32 mapiSetEventMic(input_event_t * ptrparam);
int mapiDisLd(input_raid_t * ptrparam);
int mapi_filemgt_free(output_hp_filemgt_t * ptrhead);

int mapiLock();
int mapiUnlock();
int mapiIPinfo(output_hp_ipinfo_t * ptrhead);
int mapiFreeIPinfo(output_hp_ipinfo_t * ptrhead);


