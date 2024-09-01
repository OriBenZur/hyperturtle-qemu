/*
 * vhost-vdpa.h
 *
 * Copyright(c) 2017-2018 Intel Corporation.
 * Copyright(c) 2020 Red Hat, Inc.
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */

#ifndef VHOST_VDPA_H
#define VHOST_VDPA_H
#include "standard-headers/linux/virtio_net.h"
#include "net/vhost_net.h"
#include "hw/virtio/vhost-vdpa.h"

#define TYPE_VHOST_VDPA "vhost-vdpa"

/* Todo:need to add the multiqueue support here */
typedef struct VhostVDPAState {
    NetClientState nc;
    struct vhost_vdpa vhost_vdpa;
    VHostNetState *vhost_net;

    /* Control commands shadow buffers */
    void *cvq_cmd_out_buffer;
    virtio_net_ctrl_ack *status;

    bool started;
} VhostVDPAState;


struct vhost_net *vhost_vdpa_get_vhost_net(NetClientState *nc);
void vhost_vdpa_cleanup(NetClientState *nc);
extern const int vdpa_feature_bits[];

#endif /* VHOST_VDPA_H */
