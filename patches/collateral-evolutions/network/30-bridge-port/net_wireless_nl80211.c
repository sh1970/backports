--- a/net/wireless/nl80211.c
+++ b/net/wireless/nl80211.c
@@ -2298,7 +2298,7 @@
 			       enum nl80211_iftype iftype)
 {
 	if (!use_4addr) {
-		if (netdev && (netdev->priv_flags & IFF_BRIDGE_PORT))
+		if (netdev && br_port_exists(netdev))
 			return -EBUSY;
 		return 0;
 	}
