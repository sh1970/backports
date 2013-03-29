--- a/net/bluetooth/l2cap_sock.c
+++ b/net/bluetooth/l2cap_sock.c
@@ -573,8 +573,13 @@
 	return err;
 }
 
+#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,31))
 static int l2cap_sock_setsockopt(struct socket *sock, int level, int optname,
 				 char __user *optval, unsigned int optlen)
+#else
+static int l2cap_sock_setsockopt(struct socket *sock, int level, int optname,
+				 char __user *optval, int optlen)
+#endif
 {
 	struct sock *sk = sock->sk;
 	struct l2cap_chan *chan = l2cap_pi(sk)->chan;
@@ -1225,8 +1230,12 @@
 	return sk;
 }
 
+#if defined(CONFIG_COMPAT_BT_SOCK_CREATE_NEEDS_KERN)
 static int l2cap_sock_create(struct net *net, struct socket *sock, int protocol,
 			     int kern)
+#else
+static int l2cap_sock_create(struct net *net, struct socket *sock, int protocol)
+#endif
 {
 	struct sock *sk;
 
@@ -1238,7 +1247,11 @@
 	    sock->type != SOCK_DGRAM && sock->type != SOCK_RAW)
 		return -ESOCKTNOSUPPORT;
 
+#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,32))
 	if (sock->type == SOCK_RAW && !kern && !capable(CAP_NET_RAW))
+#else
+	if (sock->type == SOCK_RAW && !capable(CAP_NET_RAW))
+#endif
 		return -EPERM;
 
 	sock->ops = &l2cap_sock_ops;
