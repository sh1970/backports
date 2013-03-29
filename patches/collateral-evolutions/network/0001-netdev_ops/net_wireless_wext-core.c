--- a/net/wireless/wext-core.c
+++ b/net/wireless/wext-core.c
@@ -925,9 +925,7 @@
 			return private(dev, iwr, cmd, info, handler);
 	}
 	/* Old driver API : call driver ioctl handler */
-	if (dev->netdev_ops->ndo_do_ioctl)
-		return dev->netdev_ops->ndo_do_ioctl(dev, ifr, cmd);
-	return -EOPNOTSUPP;
+	return ndo_do_ioctl(dev, ifr, cmd);
 }
 
 /* If command is `set a parameter', or `get the encoding parameters',
