--- a/net/mac80211/tx.c
+++ b/net/mac80211/tx.c
@@ -1512,6 +1512,10 @@
 		}
 	}
 
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,27))
+	/* Older kernels do not have the select_queue callback */
+	skb_set_queue_mapping(skb, ieee80211_select_queue(sdata, skb));
+#endif
 	ieee80211_set_qos_hdr(sdata, skb);
 	ieee80211_tx(sdata, skb, false, band);
 }
