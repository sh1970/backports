--- a/drivers/net/wireless/orinoco/orinoco_usb.c
+++ b/drivers/net/wireless/orinoco/orinoco_usb.c
@@ -1553,7 +1553,7 @@
 	.read_ltv = ezusb_read_ltv,
 	.write_ltv = ezusb_write_ltv,
 	.bap_pread = ezusb_bap_pread,
-	.read_pda = ezusb_read_pda,
+	.read_pda_h = ezusb_read_pda,
 	.program_init = ezusb_program_init,
 	.program_end = ezusb_program_end,
 	.program = ezusb_program,
