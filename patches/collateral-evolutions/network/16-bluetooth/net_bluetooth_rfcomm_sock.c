--- a/net/bluetooth/rfcomm/sock.c
+++ b/net/bluetooth/rfcomm/sock.c
@@ -304,8 +304,13 @@
 	return sk;
 }
 
+#if defined(CONFIG_COMPAT_BT_SOCK_CREATE_NEEDS_KERN)
 static int rfcomm_sock_create(struct net *net, struct socket *sock,
 			      int protocol, int kern)
+#else
+static int rfcomm_sock_create(struct net *net, struct socket *sock,
+			      int protocol)
+#endif
 {
 	struct sock *sk;
 
@@ -660,7 +665,11 @@
 	return err;
 }
 
+#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,31))
 static int rfcomm_sock_setsockopt(struct socket *sock, int level, int optname, char __user *optval, unsigned int optlen)
+#else
+static int rfcomm_sock_setsockopt(struct socket *sock, int level, int optname, char __user *optval, int optlen)
+#endif
 {
 	struct sock *sk = sock->sk;
 	struct bt_security sec;
