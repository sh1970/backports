--- a/net/bluetooth/bnep/sock.c
+++ b/net/bluetooth/bnep/sock.c
@@ -186,8 +186,12 @@
 	.obj_size	= sizeof(struct bt_sock)
 };
 
+#if defined(CONFIG_COMPAT_BT_SOCK_CREATE_NEEDS_KERN)
 static int bnep_sock_create(struct net *net, struct socket *sock, int protocol,
 			    int kern)
+#else
+static int bnep_sock_create(struct net *net, struct socket *sock, int protocol)
+#endif
 {
 	struct sock *sk;
 
