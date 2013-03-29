--- a/include/net/cfg80211.h
+++ b/include/net/cfg80211.h
@@ -2561,6 +2561,9 @@
 struct wiphy {
 	/* assign these fields before you register the wiphy */
 
+#define WIPHY_COMPAT_PAD_SIZE	2048
+	u8 padding[WIPHY_COMPAT_PAD_SIZE];
+
 	/* permanent MAC address(es) */
 	u8 perm_addr[ETH_ALEN];
 	u8 addr_mask[ETH_ALEN];
