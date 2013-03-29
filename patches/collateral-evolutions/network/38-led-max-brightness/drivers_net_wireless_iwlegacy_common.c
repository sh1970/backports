--- a/drivers/net/wireless/iwlegacy/common.c
+++ b/drivers/net/wireless/iwlegacy/common.c
@@ -562,7 +562,9 @@
 	    kasprintf(GFP_KERNEL, "%s-led", wiphy_name(il->hw->wiphy));
 	il->led.brightness_set = il_led_brightness_set;
 	il->led.blink_set = il_led_blink_set;
+#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,30)
 	il->led.max_brightness = 1;
+#endif
 
 	switch (mode) {
 	case IL_LED_DEFAULT:
