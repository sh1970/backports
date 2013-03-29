--- a/drivers/net/wireless/iwlwifi/pcie/trans.c
+++ b/drivers/net/wireless/iwlwifi/pcie/trans.c
@@ -773,12 +773,21 @@
 {
 	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
 
+#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,31)
+	compat_synchronize_threaded_irq(&trans_pcie->irq_compat);
+#else
 	synchronize_irq(trans_pcie->pci_dev->irq);
+#endif
 
 	iwl_pcie_tx_free(trans);
 	iwl_pcie_rx_free(trans);
 
+#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,31)
+	compat_free_threaded_irq(&trans_pcie->irq_compat);
+	compat_destroy_threaded_irq(&trans_pcie->irq_compat);
+#else
 	free_irq(trans_pcie->pci_dev->irq, trans);
+#endif
 	iwl_pcie_free_ict(trans);
 
 	pci_disable_msi(trans_pcie->pci_dev);
@@ -1566,9 +1575,16 @@
 	if (iwl_pcie_alloc_ict(trans))
 		goto out_free_cmd_pool;
 
+#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,31)
+	if (compat_request_threaded_irq(&trans_pcie->irq_compat,
+					pdev->irq, iwl_pcie_isr_ict,
+					iwl_pcie_irq_handler,
+					IRQF_SHARED, DRV_NAME, trans)) {
+#else
 	if (request_threaded_irq(pdev->irq, iwl_pcie_isr_ict,
 				 iwl_pcie_irq_handler,
 				 IRQF_SHARED, DRV_NAME, trans)) {
+#endif
 		IWL_ERR(trans, "Error allocating IRQ %d\n", pdev->irq);
 		goto out_free_ict;
 	}
