#ifndef _LBWM_ATOMS
#define _LBWM_ATOMS

enum WMAtoms {
    WMAtoms_Protocols,
    WMAtoms_DeleteWindow,
    WMAtoms_State,
    WMAtoms_TakeFocus,
    WMAtoms_COUNT
};

enum NetAtoms{
    NetAtoms_ActiveWindow,
    NetAtoms_Supported,
    NetAtoms_WmName,
    NetAtoms_WmState,
    NetAtoms_SupportingWmCheck,
    NetAtoms_WmStateFullscreen,
    NetAtoms_WmWindowType,
    NetAtoms_WmWindowTypeDialog,
    NetAtoms_ClientList,
    NetAtoms_COUNT
};
#endif // _LBWM_ATOMS
