--- a/net/bluetooth/hci_sysfs.c
+++ b/net/bluetooth/hci_sysfs.c
@@ -72,7 +72,11 @@
 	.attrs = bt_link_attrs,
 };
 
+#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,31))
 static const struct attribute_group *bt_link_groups[] = {
+#else
+static struct attribute_group *bt_link_groups[] = {
+#endif
 	&bt_link_group,
 	NULL
 };
@@ -141,7 +145,11 @@
 		dev = device_find_child(&conn->dev, NULL, __match_tty);
 		if (!dev)
 			break;
+#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,29))
 		device_move(dev, NULL, DPM_ORDER_DEV_LAST);
+#else
+		device_move(dev, NULL);
+#endif
 		put_device(dev);
 	}
 
@@ -379,7 +387,11 @@
 	.attrs = bt_host_attrs,
 };
 
+#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,31))
 static const struct attribute_group *bt_host_groups[] = {
+#else
+static struct attribute_group *bt_host_groups[] = {
+#endif
 	&bt_host_group,
 	NULL
 };
