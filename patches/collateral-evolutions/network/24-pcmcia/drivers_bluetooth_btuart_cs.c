--- a/drivers/bluetooth/btuart_cs.c
+++ b/drivers/bluetooth/btuart_cs.c
@@ -140,7 +140,11 @@
 	}
 
 	do {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 		unsigned int iobase = info->p_dev->resource[0]->start;
+#else
+		unsigned int iobase = info->p_dev->io.BasePort1;
+#endif
 		register struct sk_buff *skb;
 		int len;
 
@@ -181,7 +185,11 @@
 		return;
 	}
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 	iobase = info->p_dev->resource[0]->start;
+#else
+	iobase = info->p_dev->io.BasePort1;
+#endif
 
 	do {
 		info->hdev->stat.byte_rx++;
@@ -295,7 +303,11 @@
 		/* our irq handler is shared */
 		return IRQ_NONE;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 	iobase = info->p_dev->resource[0]->start;
+#else
+	iobase = info->p_dev->io.BasePort1;
+#endif
 
 	spin_lock(&(info->lock));
 
@@ -352,7 +364,11 @@
 		return;
 	}
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 	iobase = info->p_dev->resource[0]->start;
+#else
+	iobase = info->p_dev->io.BasePort1;
+#endif
 
 	spin_lock_irqsave(&(info->lock), flags);
 
@@ -471,7 +487,11 @@
 static int btuart_open(btuart_info_t *info)
 {
 	unsigned long flags;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 	unsigned int iobase = info->p_dev->resource[0]->start;
+#else
+	unsigned int iobase = info->p_dev->io.BasePort1;
+#endif
 	struct hci_dev *hdev;
 
 	spin_lock_init(&(info->lock));
@@ -538,7 +558,11 @@
 static int btuart_close(btuart_info_t *info)
 {
 	unsigned long flags;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 	unsigned int iobase = info->p_dev->resource[0]->start;
+#else
+	unsigned int iobase = info->p_dev->io.BasePort1;
+#endif
 	struct hci_dev *hdev = info->hdev;
 
 	if (!hdev)
@@ -574,8 +598,27 @@
 	info->p_dev = link;
 	link->priv = info;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
 	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_VPP |
 		CONF_AUTO_SET_IO;
+#else
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
+	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;
+	link->resource[0]->end = 8;
+#else
+	link->io.Attributes1 = IO_DATA_PATH_WIDTH_8;
+	link->io.NumPorts1= 8;
+#endif
+
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
+	link->irq.Attributes = IRQ_TYPE_DYNAMIC_SHARING;
+
+	link->irq.Handler = btuart_interrupt;
+#endif
+
+	link->conf.Attributes = CONF_ENABLE_IRQ;
+	link->conf.IntType = INT_MEMORY_AND_IO;
+#endif
 
 	return btuart_config(link);
 }
@@ -586,6 +629,7 @@
 	btuart_release(link);
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
 static int btuart_check_config(struct pcmcia_device *p_dev, void *priv_data)
 {
 	int *try = priv_data;
@@ -624,6 +668,63 @@
 	}
 	return -ENODEV;
 }
+#else
+static int btuart_check_config(struct pcmcia_device *p_dev,
+			       cistpl_cftable_entry_t *cf,
+			       cistpl_cftable_entry_t *dflt,
+			       unsigned int vcc,
+			       void *priv_data)
+{
+	int *try = priv_data;
+
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
+	p_dev->io_lines = (try == 0) ? 16 : cf->io.flags & CISTPL_IO_LINES_MASK;
+#endif
+
+	if (cf->vpp1.present & (1 << CISTPL_POWER_VNOM))
+		p_dev->conf.Vpp = cf->vpp1.param[CISTPL_POWER_VNOM] / 10000;
+	if ((cf->io.nwin > 0) && (cf->io.win[0].len == 8) &&
+	    (cf->io.win[0].base != 0)) {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
+		p_dev->resource[0]->start = cf->io.win[0].base;
+		if (!pcmcia_request_io(p_dev))
+#else
+		p_dev->io.BasePort1 = cf->io.win[0].base;
+		p_dev->io.IOAddrLines = (*try == 0) ? 16 :
+			cf->io.flags & CISTPL_IO_LINES_MASK;
+		if (!pcmcia_request_io(p_dev, &p_dev->io))
+#endif
+			return 0;
+	}
+	return -ENODEV;
+}
+
+static int btuart_check_config_notpicky(struct pcmcia_device *p_dev,
+					cistpl_cftable_entry_t *cf,
+					cistpl_cftable_entry_t *dflt,
+					unsigned int vcc,
+					void *priv_data)
+{
+	static unsigned int base[5] = { 0x3f8, 0x2f8, 0x3e8, 0x2e8, 0x0 };
+	int j;
+
+	if ((cf->io.nwin > 0) && ((cf->io.flags & CISTPL_IO_LINES_MASK) <= 3)) {
+		for (j = 0; j < 5; j++) {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
+			p_dev->resource[0]->start = base[j];
+			p_dev->io_lines = base[j] ? 16 : 3;
+			if (!pcmcia_request_io(p_dev))
+#else
+			p_dev->io.BasePort1 = base[j];
+			p_dev->io.IOAddrLines = base[j] ? 16 : 3;
+			if (!pcmcia_request_io(p_dev, &p_dev->io))
+#endif
+				return 0;
+		}
+	}
+	return -ENODEV;
+}
+#endif
 
 static int btuart_config(struct pcmcia_device *link)
 {
@@ -647,9 +748,15 @@
 	goto failed;
 
 found_port:
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	i = pcmcia_request_irq(link, btuart_interrupt);
 	if (i != 0)
 		goto failed;
+#else
+	i = pcmcia_request_irq(link, &link->irq);
+	if (i != 0)
+		link->irq.AssignedIRQ = 0;
+#endif
 
 	i = pcmcia_enable_device(link);
 	if (i != 0)
@@ -683,7 +790,13 @@
 
 static struct pcmcia_driver btuart_driver = {
 	.owner		= THIS_MODULE,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
 	.name		= "btuart_cs",
+#else
+	.drv		= {
+		.name	= "btuart_cs",
+	},
+#endif
 	.probe		= btuart_probe,
 	.remove		= btuart_detach,
 	.id_table	= btuart_ids,
