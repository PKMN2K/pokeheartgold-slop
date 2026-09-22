#include "global.h"

#include "heap.h"
#include "overlay_01_021FB4C0_internal.h"
#include "system.h"

static void ov01_021FB55C(UnkStruct_Ov01_021FB4C0 *manager);
static void ov01_021FB584(UnkStruct_Ov01_021FB4C0_sub *slot);
static void ov01_021FB594(void *arg);
static void ov01_021FB5B0(void *param0, void *param1);
static UnkStruct_Ov01_021FB4C0_sub *ov01_021FB5B4(UnkStruct_Ov01_021FB4C0 *manager);

UnkStruct_Ov01_021FB4C0 *HBlankSystem_New(enum HeapID heapId) {
    UnkStruct_Ov01_021FB4C0 *manager = Heap_Alloc(heapId, sizeof(UnkStruct_Ov01_021FB4C0));
    ov01_021FB55C(manager);
    return manager;
}

void HBlankSystem_Delete(UnkStruct_Ov01_021FB4C0 *manager) {
    if (manager != NULL) {
        if (manager->state == 1) {
            HBlankSystem_Stop(manager);
        }
        ov01_021FB55C(manager);
        Heap_Free(manager);
    }
}

void HBlankSystem_Start(UnkStruct_Ov01_021FB4C0 *manager) {
    GF_ASSERT(Main_SetHBlankIntrCB(ov01_021FB594, manager) == TRUE);
    manager->state = 1;
}

void HBlankSystem_Stop(UnkStruct_Ov01_021FB4C0 *manager) {
    GF_ASSERT(Main_SetHBlankIntrCB(NULL, NULL) == TRUE);
    manager->state = 0;
}

UnkStruct_Ov01_021FB4C0_sub *ov01_021FB530(UnkStruct_Ov01_021FB4C0 *manager, UnkFuncPtr_Ov01_021FB4C0 callback, void *data) {
    UnkStruct_Ov01_021FB4C0_sub *slot = ov01_021FB5B4(manager);
    GF_ASSERT(slot != NULL);
    if (slot != NULL) {
        slot->data = data;
        slot->callback = callback;
        slot->used = 1;
    }
    return slot;
}

void ov01_021FB554(UnkStruct_Ov01_021FB4C0_sub *slot) {
    ov01_021FB584(slot);
}

static void ov01_021FB55C(UnkStruct_Ov01_021FB4C0 *manager) {
    u8 *p = (u8 *)manager;
    u32 size = sizeof(UnkStruct_Ov01_021FB4C0);

    do {
        *p++ = 0;
    } while (--size);

    {
        register int i = 0;
        manager->state = i;
        for (; i < 2; i++) {
            ov01_021FB584(&manager->slots[i]);
        }
    }
}


static void ov01_021FB584(UnkStruct_Ov01_021FB4C0_sub *slot) {
    slot->used = 0;
    slot->callback = ov01_021FB5B0;
    slot->data = NULL;
}

static void ov01_021FB594(void *arg) {
    UnkStruct_Ov01_021FB4C0 *manager = arg;
    int i;
    for (i = 0; i < 2; i++) {
        manager->slots[i].callback(&manager->slots[i], manager->slots[i].data);
    }
}

static void ov01_021FB5B0(void *param0, void *param1) {
}

static UnkStruct_Ov01_021FB4C0_sub *ov01_021FB5B4(UnkStruct_Ov01_021FB4C0 *manager) {
    int i;
    for (i = 0; i < 2; i++) {
        if (manager->slots[i].used == 0) {
            return &manager->slots[i];
        }
    }
    return NULL;
}
