#ifndef __BACKPORT_CHECKS
#define __BACKPORT_CHECKS

#if defined(CPTCFG_BACKPORT_KERNEL_2_6_28) && defined(CONFIG_DYNAMIC_FTRACE)
#error "You can't build on a 2.6.27 or older kernel with dynamic ftrace, it's broken"
#endif

#if defined(CONFIG_MAC80211) && defined(CPTCFG_MAC80211)
#error "You must not have mac80211 built into your kernel if you want to enable it"
#endif

#if defined(CONFIG_CFG80211) && defined(CPTCFG_CFG80211)
#error "You must not have cfg80211 built into your kernel if you want to enable it"
#endif

#endif /* __BACKPORT_CHECKS */
