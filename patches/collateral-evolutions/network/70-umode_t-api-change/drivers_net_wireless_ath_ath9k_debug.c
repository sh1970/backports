--- a/drivers/net/wireless/ath/ath9k/debug.c
+++ b/drivers/net/wireless/ath/ath9k/debug.c
@@ -1217,7 +1217,11 @@
 
 static struct dentry *create_buf_file_handler(const char *filename,
 					      struct dentry *parent,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,3,0))
 					      umode_t mode,
+#else
+					      int mode,
+#endif
 					      struct rchan_buf *buf,
 					      int *is_global)
 {
