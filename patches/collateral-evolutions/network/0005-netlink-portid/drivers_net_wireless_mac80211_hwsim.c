--- a/drivers/net/wireless/mac80211_hwsim.c
+++ b/drivers/net/wireless/mac80211_hwsim.c
@@ -2019,10 +2019,10 @@
 	if (info == NULL)
 		goto out;
 
-	wmediumd_portid = info->snd_portid;
+	wmediumd_portid = genl_info_snd_portid(info);
 
 	printk(KERN_DEBUG "mac80211_hwsim: received a REGISTER, "
-	       "switching to wmediumd mode with pid %d\n", info->snd_portid);
+	       "switching to wmediumd mode with pid %d\n", genl_info_snd_portid(info));
 
 	return 0;
 out:
@@ -2059,7 +2059,7 @@
 	if (state != NETLINK_URELEASE)
 		return NOTIFY_DONE;
 
-	if (notify->portid == wmediumd_portid) {
+	if (netlink_notify_portid(notify) == wmediumd_portid) {
 		printk(KERN_INFO "mac80211_hwsim: wmediumd released netlink"
 		       " socket, switching to perfect channel medium\n");
 		wmediumd_portid = 0;
