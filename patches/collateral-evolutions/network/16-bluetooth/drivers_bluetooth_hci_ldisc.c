--- a/drivers/bluetooth/hci_ldisc.c
+++ b/drivers/bluetooth/hci_ldisc.c
@@ -297,8 +297,13 @@
 	/* FIXME: why is this needed. Note don't use ldisc_ref here as the
 	   open path is before the ldisc is referencable */
 
+#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,30))
 	if (tty->ldisc->ops->flush_buffer)
 		tty->ldisc->ops->flush_buffer(tty);
+#else
+	if (tty->ldisc.ops->flush_buffer)
+		tty->ldisc.ops->flush_buffer(tty);
+#endif
 	tty_driver_flush_buffer(tty);
 
 	return 0;
@@ -524,7 +529,11 @@
 		return hu->hdev_flags;
 
 	default:
+#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,27))
 		err = n_tty_ioctl_helper(tty, file, cmd, arg);
+#else
+		err = n_tty_ioctl(tty, file, cmd, arg);
+#endif
 		break;
 	}
 
