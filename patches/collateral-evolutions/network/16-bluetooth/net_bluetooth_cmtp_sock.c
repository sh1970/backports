--- a/net/bluetooth/cmtp/sock.c
+++ b/net/bluetooth/cmtp/sock.c
@@ -195,8 +195,12 @@
 	.obj_size	= sizeof(struct bt_sock)
 };
 
+#if defined(CONFIG_COMPAT_BT_SOCK_CREATE_NEEDS_KERN)
 static int cmtp_sock_create(struct net *net, struct socket *sock, int protocol,
 			    int kern)
+#else
+static int cmtp_sock_create(struct net *net, struct socket *sock, int protocol)
+#endif
 {
 	struct sock *sk;
 
