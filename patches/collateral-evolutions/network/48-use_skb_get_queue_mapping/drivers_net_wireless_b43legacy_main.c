--- a/drivers/net/wireless/b43legacy/main.c
+++ b/drivers/net/wireless/b43legacy/main.c
@@ -2529,11 +2529,11 @@
 	}
 	B43legacy_WARN_ON(skb_shinfo(skb)->nr_frags);
 
-	skb_queue_tail(&wl->tx_queue[skb->queue_mapping], skb);
-	if (!wl->tx_queue_stopped[skb->queue_mapping])
+	skb_queue_tail(&wl->tx_queue[skb_get_queue_mapping(skb)], skb);
+	if (!wl->tx_queue_stopped[skb_get_queue_mapping(skb)])
 		ieee80211_queue_work(wl->hw, &wl->tx_work);
 	else
-		ieee80211_stop_queue(wl->hw, skb->queue_mapping);
+		ieee80211_stop_queue(wl->hw, skb_get_queue_mapping(skb));
 }
 
 static int b43legacy_op_conf_tx(struct ieee80211_hw *hw,
