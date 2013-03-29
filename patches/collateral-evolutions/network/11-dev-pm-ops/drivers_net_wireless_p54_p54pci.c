--- a/drivers/net/wireless/p54/p54pci.c
+++ b/drivers/net/wireless/p54/p54pci.c
@@ -684,6 +684,9 @@
 	return pci_set_power_state(pdev, PCI_D0);
 }
 
+compat_pci_suspend(p54p_suspend);
+compat_pci_resume(p54p_resume);
+
 static SIMPLE_DEV_PM_OPS(p54pci_pm_ops, p54p_suspend, p54p_resume);
 
 #define P54P_PM_OPS (&p54pci_pm_ops)
@@ -696,7 +699,12 @@
 	.id_table	= p54p_table,
 	.probe		= p54p_probe,
 	.remove		= p54p_remove,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29))
 	.driver.pm	= P54P_PM_OPS,
+#elif defined(CONFIG_PM_SLEEP)
+	.suspend    = p54p_suspend_compat,
+	.resume     = p54p_resume_compat,
+#endif
 };
 
 module_pci_driver(p54p_driver);
