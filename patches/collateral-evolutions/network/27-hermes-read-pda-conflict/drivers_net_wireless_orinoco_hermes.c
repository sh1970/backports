--- a/drivers/net/wireless/orinoco/hermes.c
+++ b/drivers/net/wireless/orinoco/hermes.c
@@ -767,7 +767,7 @@
 	.write_ltv = hermes_write_ltv,
 	.bap_pread = hermes_bap_pread,
 	.bap_pwrite = hermes_bap_pwrite,
-	.read_pda = hermes_read_pda,
+	.read_pda_h = hermes_read_pda,
 	.program_init = hermesi_program_init,
 	.program_end = hermesi_program_end,
 	.program = hermes_program_bytes,
