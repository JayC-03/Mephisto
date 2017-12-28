#include "Ctu.h"

#define __in
#define __out
#define __inout

typedef struct {
    uint32_t arch;                           // 0x120 (NVGPU_GPU_ARCH_GM200)
    uint32_t impl;                           // 0xB (NVGPU_GPU_IMPL_GM20B)
    uint32_t rev;                            // 0xA1 (Revision A1)
    uint32_t num_gpc;                        // 0x1
    uint64_t L2_cache_size;                  // 0x40000
    uint64_t on_board_video_memory_size;     // 0x0 (not used)
    uint32_t num_tpc_per_gpc;                // 0x2
    uint32_t bus_type;                       // 0x20 (NVGPU_GPU_BUS_TYPE_AXI)
    uint32_t big_page_size;                  // 0x20000
    uint32_t compression_page_size;          // 0x20000
    uint32_t pde_coverage_bit_count;         // 0x1B
    uint32_t available_big_page_sizes;       // 0x30000
    uint32_t gpc_mask;                       // 0x1
    uint32_t sm_arch_sm_version;             // 0x503 (Maxwell Generation 5.0.3?)
    uint32_t sm_arch_spa_version;            // 0x503 (Maxwell Generation 5.0.3?)
    uint32_t sm_arch_warp_count;             // 0x80
    uint32_t gpu_va_bit_count;               // 0x28
    uint32_t reserved;                       // NULL
    uint64_t flags;                          // 0x55
    uint32_t twod_class;                     // 0x902D (FERMI_TWOD_A)
    uint32_t threed_class;                   // 0xB197 (MAXWELL_B)
    uint32_t compute_class;                  // 0xB1C0 (MAXWELL_COMPUTE_B)
    uint32_t gpfifo_class;                   // 0xB06F (MAXWELL_CHANNEL_GPFIFO_A)
    uint32_t inline_to_memory_class;         // 0xA140 (KEPLER_INLINE_TO_MEMORY_B)
    uint32_t dma_copy_class;                 // 0xB0B5 (MAXWELL_DMA_COPY_A)
    uint32_t max_fbps_count;                 // 0x1
    uint32_t fbp_en_mask;                    // 0x0 (disabled)
    uint32_t max_ltc_per_fbp;                // 0x2
    uint32_t max_lts_per_ltc;                // 0x1
    uint32_t max_tex_per_tpc;                // 0x0 (not supported)
    uint32_t max_gpc_count;                  // 0x1
    uint32_t rop_l2_en_mask_0;               // 0x21D70 (fuse_status_opt_rop_l2_fbp_r)
    uint32_t rop_l2_en_mask_1;               // 0x0
    uint64_t chipname;                       // 0x6230326D67 ("gm20b")
    uint64_t gr_compbit_store_base_hw;       // 0x0 (not supported)
} gpu_characteristics;

typedef struct {
	__in  uint64_t gc_buf_size;   // must not be NULL, but gets overwritten with 0xA0=max_size
	__in  uint64_t gc_buf_addr;   // ignored, but must not be NULL
	__out gpu_characteristics gc;
} gpu_characteristics_data;

typedef struct {
    uint64_t offset;
    uint32_t page_size;
    uint32_t pad;
    uint64_t pages;
} nv_va_region;

typedef struct {
    uint64_t not_used;        // contained output user ptr on linux, ignored
    __inout uint32_t bufsize; // forced to 2*sizeof(struct va_region)
    uint32_t pad;
    __out nv_va_region regions[2];
} nv_get_varegions_data;

uint32_t NvidiaService::Ioctl(IN uint32_t fd, IN uint32_t request, IN uint8_t * inbuf, guint inbuf_size, OUT uint8_t * outbuf, guint outbuf_size, OUT uint32_t& error_code) {
	uint32_t *outbuf4 = (uint32_t*)outbuf;
	memset(outbuf, 0, outbuf_size);
	error_code = 0;

	memcpy(outbuf, inbuf, outbuf_size > inbuf_size ? inbuf_size : outbuf_size);

	guint pos;
	printf("NvidiaService::Ioctl outbuf with fd=0x%x request=0x%x:\n", fd, request);
	for(pos=0; pos<outbuf_size; pos++)printf("%02x", outbuf[pos]);
	printf("\n");

	if(request==0xC0B04705) {//NVGPU_GPU_IOCTL_GET_CHARACTERISTICS
		gpu_characteristics_data *data = (gpu_characteristics_data*)outbuf;
		if(sizeof(gpu_characteristics_data) > outbuf_size)return -1;

		data->gc_buf_size = 0xA0;

		data->gc.arch = 0x120;// (NVGPU_GPU_ARCH_GM200)
		data->gc.impl = 0xB;// (NVGPU_GPU_IMPL_GM20B)
		data->gc.rev = 0xA1;// (Revision A1)
		data->gc.num_gpc = 0x1;
		data->gc.L2_cache_size = 0x40000;//
		data->gc.on_board_video_memory_size = 0x0;// (not used)
		data->gc.num_tpc_per_gpc = 0x2;
		data->gc.bus_type = 0x20;// (NVGPU_GPU_BUS_TYPE_AXI)
		data->gc.big_page_size = 0x20000;
		data->gc.compression_page_size = 0x20000;
		data->gc.pde_coverage_bit_count = 0x1B;
		data->gc.available_big_page_sizes = 0x30000;
		data->gc.gpc_mask = 0x1;
		data->gc.sm_arch_sm_version = 0x503;// (Maxwell Generation 5.0.3?)
		data->gc.sm_arch_spa_version = 0x503;// (Maxwell Generation 5.0.3?)
		data->gc.sm_arch_warp_count = 0x80;
		data->gc.gpu_va_bit_count = 0x28;
		data->gc.reserved = 0;
		data->gc.flags = 0x55;
		data->gc.twod_class = 0x902D;// (FERMI_TWOD_A)
		data->gc.threed_class = 0xB197;// (MAXWELL_B)
		data->gc.compute_class = 0xB1C0;// (MAXWELL_COMPUTE_B)
		data->gc.gpfifo_class = 0xB06F;// (MAXWELL_CHANNEL_GPFIFO_A)
		data->gc.inline_to_memory_class = 0xA140;// (KEPLER_INLINE_TO_MEMORY_B)
		data->gc.dma_copy_class = 0xB0B5;// (MAXWELL_DMA_COPY_A)
		data->gc.max_fbps_count = 0x1;
		data->gc.fbp_en_mask = 0x0;// (disabled)
		data->gc.max_ltc_per_fbp = 0x2;
		data->gc.max_lts_per_ltc = 0x1;
		data->gc.max_tex_per_tpc = 0x0;// (not supported)
		data->gc.max_gpc_count = 0x1;
		data->gc.rop_l2_en_mask_0 = 0x21D70;// (fuse_status_opt_rop_l2_fbp_r)
		data->gc.rop_l2_en_mask_1 = 0x0;
		data->gc.chipname = 0x6230326D67;// ("gm20b")
		data->gc.gr_compbit_store_base_hw = 0x0;// (not supported)
	}
	//else if(request==0xC0284106) {
	//}
	else if(request==0xC0184706) {//NVGPU_GPU_IOCTL_GET_TPC_MASKS 
		if(24 > outbuf_size)return -1;

		outbuf4[4] = 0x3;
	}
	else if(request==0x80044701) {//NVGPU_GPU_IOCTL_ZCULL_GET_CTX_SIZE
		if(0x4 > outbuf_size)return -1;

		outbuf4[0] = 0x10200;
	}
	else if(request==0x80284702) {//NVGPU_GPU_IOCTL_ZCULL_GET_INFO
		if(0x28 > outbuf_size)return -1;

		outbuf4[0] = 0x20;
		outbuf4[1] = 0x20;
		outbuf4[2] = 0x400;
		outbuf4[3] = 0x800;
		outbuf4[4] = 0x20;
		outbuf4[5] = 0x20;
		outbuf4[6] = 0xc0;
		outbuf4[7] = 0x20;
		outbuf4[8] = 0x40;
		outbuf4[9] = 0x10;
	}
	else if(request==0xC0404108) {
		nv_get_varegions_data *data = (nv_get_varegions_data*)outbuf;
		if(sizeof(nv_get_varegions_data) > outbuf_size)return -1;

		if(data->bufsize==0)return 0;

		data->bufsize = 0x30;

		data->regions[0].offset = 0x04000000;
		data->regions[0].page_size = 0x1000;
		data->regions[0].pages = 0x3fbfff;

		data->regions[1].offset = 0x04000000;
		data->regions[1].page_size = 0x10000;
		data->regions[1].pages = 0x1bffff;
	}
	else if(request==0xC0284106) {
		//memset(outbuf, 0x88, outbuf_size);
	}

	return 0;
}

uint32_t NvidiaService::QueryEvent(IN uint32_t fd, IN uint32_t event_id, OUT uint32_t& error_code, OUT shared_ptr<KObject>& event) {
	event = make_shared<Waitable>();
	return 0;
}

