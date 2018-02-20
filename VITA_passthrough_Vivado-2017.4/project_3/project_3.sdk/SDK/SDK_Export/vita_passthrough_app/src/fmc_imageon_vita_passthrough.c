//----------------------------------------------------------------
//      _____
//     /     \
//    /____   \____
//   / \===\   \==/
//  /___\===\___\/  AVNET
//       \======/
//        \====/
//---------------------------------------------------------------
//
// This design is the property of Avnet.  Publication of this
// design is not authorized without written consent from Avnet.
//
// Please direct any questions to:  technical.support@avnet.com
//
// Disclaimer:
//    Avnet, Inc. makes no warranty for the use of this code or design.
//    This code is provided  "As Is". Avnet, Inc assumes no responsibility for
//    any errors, which may appear in this code, nor does it make a commitment
//    to update the information contained herein. Avnet, Inc specifically
//    disclaims any implied warranties of fitness for a particular purpose.
//                     Copyright(c) 2011 Avnet, Inc.
//                             All rights reserved.
//
//----------------------------------------------------------------
//
// Create Date:         Nov 15, 2011
// Design Name:         FMC-IMAGEON VITA Passthrough
// Module Name:         fmc_imageon_vita_passthrough.c
// Project Name:        FMC-IMAGEON VITA Passthrough Program
// Target Devices:      Zynq
// Hardware Boards:     FMC-IMAGEON
// 
//
// Tool versions:       Vivado 2013.3
//
// Description:         FMC-IMAGEON VITA Demo Program
//                      This application will configure the FMC-IMAGEON module
//                      for the simple case of an HDMI passthrough:
//                      - VITA Input
//                         - VITA sensor configured for 1080P60 resolution
//                      - HDMI Output
//                         - ADV7511 configured for 16 bit YCbCr 4:2:2 mode
//                           with embedded syncs
//                      If present, it will also reset the Video Timing Controller
//                      that is used for timing in the AXI4-Stream bridges
//
// Dependencies:
//
// Revision:            Dec 20, 2013: 1.00 Initial version
//
//----------------------------------------------------------------

#include <stdio.h>

#include "fmc_imageon_vita_passthrough.h"


int fmc_imageon_vita_passthrough_init( fmc_imageon_vita_passthrough_t *pDemo )
{
   int ret;
   Xuint32 timeout = 100;
   Xuint32 iterations = 0;

   xil_printf("\n\r");
   xil_printf("------------------------------------------------------\n\r");
   xil_printf("--          FMC-IMAGEON VITA Pass-Through           --\n\r");
   xil_printf("------------------------------------------------------\n\r");
   xil_printf("\n\r");

   xil_printf( "FMC-IMAGEON Initialization ...\n\r" );

   ret = fmc_iic_xps_init(&(pDemo->fmc_imageon_iic),"FMC-IMAGEON I2C Controller", pDemo->uBaseAddr_IIC_FmcImageon );
   if ( !ret )
   {
      xil_printf( "ERROR : Failed to open FMC-IIC driver\n\r" );
      exit(0);
   }

   fmc_imageon_init(&(pDemo->fmc_imageon), "FMC-IMAGEON", &(pDemo->fmc_imageon_iic));
   pDemo->fmc_imageon.bVerbose = pDemo->bVerbose;

   // Configure Video Clock Synthesizer
   xil_printf( "Video Clock Synthesizer Configuration ...\n\r" );
   fmc_imageon_vclk_init( &(pDemo->fmc_imageon) );
   fmc_imageon_vclk_config( &(pDemo->fmc_imageon), FMC_IMAGEON_VCLK_FREQ_148_500_000);
   sleep(1);

   // Set HDMI output to 1080P60
   pDemo->hdmio_resolution = VIDEO_RESOLUTION_1080P;
   pDemo->hdmio_width  = 1920;
   pDemo->hdmio_height = 1080;

   //pDemo->hdmio_timing.IsHDMI        = 1; // HDMI Mode
   pDemo->hdmio_timing.IsHDMI        = 0; // DVI Mode
   pDemo->hdmio_timing.IsEncrypted   = 0;
   pDemo->hdmio_timing.IsInterlaced  = 0;
   pDemo->hdmio_timing.ColorDepth    = 8;

   pDemo->hdmio_timing.HActiveVideo  = 1920;
   pDemo->hdmio_timing.HFrontPorch   =   88;
   pDemo->hdmio_timing.HSyncWidth    =   44;
   pDemo->hdmio_timing.HSyncPolarity =    1;
   pDemo->hdmio_timing.HBackPorch    =  148;

   pDemo->hdmio_timing.VActiveVideo  = 1080;
   pDemo->hdmio_timing.VFrontPorch   =    4;
   pDemo->hdmio_timing.VSyncWidth    =    5;
   pDemo->hdmio_timing.VSyncPolarity =    1;
   pDemo->hdmio_timing.VBackPorch    =   36;

   xil_printf( "ADV7511 Video Output Information\n\r" );
   xil_printf( "\tVideo Output     = %s", pDemo->hdmio_timing.IsHDMI ? "HDMI" : "DVI" );
   xil_printf( "%s", pDemo->hdmio_timing.IsEncrypted ? ", HDCP Encrypted" : "" );
   xil_printf( ", %s\n\r", pDemo->hdmio_timing.IsInterlaced ? "Interlaced" : "Progressive" );
   xil_printf( "\tColor Depth      = %d bits per channel\n\r", pDemo->hdmio_timing.ColorDepth );
   xil_printf( "\tHSYNC Timing     = hav=%04d, hfp=%02d, hsw=%02d(hsp=%d), hbp=%03d\n\r",
      pDemo->hdmio_timing.HActiveVideo,
      pDemo->hdmio_timing.HFrontPorch,
      pDemo->hdmio_timing.HSyncWidth, pDemo->hdmio_timing.HSyncPolarity,
      pDemo->hdmio_timing.HBackPorch
      );
   xil_printf( "\tVSYNC Timing     = vav=%04d, vfp=%02d, vsw=%02d(vsp=%d), vbp=%03d\n\r",
      pDemo->hdmio_timing.VActiveVideo,
      pDemo->hdmio_timing.VFrontPorch,
      pDemo->hdmio_timing.VSyncWidth, pDemo->hdmio_timing.VSyncPolarity,
      pDemo->hdmio_timing.VBackPorch
      );
   xil_printf( "\tVideo Dimensions = %d x %d\n\r", pDemo->hdmio_width, pDemo->hdmio_height );

   xil_printf( "HDMI Output Initialization ...\n\r" );
   ret = fmc_imageon_hdmio_init( &(pDemo->fmc_imageon),
 	                             1,                      // hdmioEnable = 1
 	                             &(pDemo->hdmio_timing), // pTiming
 	                             0                       // waitHPD = 0
 	                             );
   if ( !ret )
   {
      xil_printf( "ERROR : Failed to init HDMI Output Interface\n\r" );
      exit(0);
   }

  while (1)
  {

   if ( iterations > 0 )
   {
      xil_printf( "\n\rPress ENTER to re-start ...\n\r" );
      getchar();
   }
   iterations++;

   // FMC-IMAGEON VITA Receiver Initialization
   xil_printf( "FMC-IMAGEON VITA Receiver Initialization ...\n\r" );
   fmc_imageon_vita_receiver_init( &(pDemo->vita_receiver), "VITA-2000", pDemo->uBaseAddr_VITA_Receiver );
   pDemo->vita_receiver.uManualTap = 25;
   xil_printf( "FMC-IMAGEON VITA SPI Config for 10MHz ...\n\r" );
   // axi4lite_0_clk = 50MHz
   fmc_imageon_vita_receiver_spi_config( &(pDemo->vita_receiver), (50000000/10000000) );

   // VITA-2000 Initialization
   xil_printf( "FMC-IMAGEON VITA Initialization ...\n\r" );
   ret = fmc_imageon_vita_receiver_sensor_initialize( &(pDemo->vita_receiver), SENSOR_INIT_ENABLE, pDemo->bVerbose );
   if ( ret == 0 )
   {
       xil_printf( "VITA sensor failed to initialize ...\n\r" );
      //return -1;
      return XST_SUCCESS;
   }

   sleep(1);

   xil_printf( "FMC-IMAGEON VITA Configuration for 1080P60 timing ...\n\r" );
   ret = fmc_imageon_vita_receiver_sensor_1080P60( &(pDemo->vita_receiver), pDemo->bVerbose );
   if ( ret == 0 )
   {
      xil_printf( "VITA sensor failed to configure for 1080P60 timing ...\n\r" );
      //return -1;
      return XST_SUCCESS;
   }

   sleep(1);
   fmc_imageon_vita_receiver_get_status( &(pDemo->vita_receiver), &(pDemo->vita_status_t1), 0 );
   sleep(1);
   fmc_imageon_vita_receiver_get_status( &(pDemo->vita_receiver), &(pDemo->vita_status_t2), 0 );
   //
   xil_printf( "VITA Status = \n\r" );
   xil_printf("\tImage Width  = %d\n\r", pDemo->vita_status_t1.cntImagePixels * 4 );
   xil_printf("\tImage Height = %d\n\r", pDemo->vita_status_t1.cntImageLines  );
   xil_printf("\tFrame Rate   = %d frames/sec\n\r", pDemo->vita_status_t2.cntFrames - pDemo->vita_status_t1.cntFrames );
   xil_printf("\tCRC Status   = %X\n\r", pDemo->vita_status_t2.crcStatus );

   if ( pDemo->bVerbose )
   {
   	fmc_imageon_vita_receiver_get_status( &(pDemo->vita_receiver), &(pDemo->vita_status_t2), 1 );
   }

#if 0
   // accept 1920x1080 resolution
   if ( (pDemo->vita_status_t1.cntImagePixels * 4)==1920 && (pDemo->vita_status_t1.cntImageLines)==1080 )
   {
   	// accept 60-64fps range
   	if ( (pDemo->vita_status_t2.cntFrames - pDemo->vita_status_t1.cntFrames)>=60 && (pDemo->vita_status_t2.cntFrames - pDemo->vita_status_t1.cntFrames)<=64 )
   	{
           ; //break;
   	}
   }
#endif


#if defined(XPAR_XVTC_NUM_INSTANCES)
   // Configure VTC on output data path
   xil_printf( "Video Timing Controller (generator) Initialization ...\n\r" );
   vgen_init( &(pDemo->vtc_hdmio_generator), pDemo->uDeviceId_VTC_HdmioGenerator );
   vgen_config( &(pDemo->vtc_hdmio_generator), pDemo->hdmio_resolution, 1 );
#endif

//#if defined(XPAR_CFA_NUM_INSTANCES)
#if defined(XPAR_CFA_0_BASEADDR)
   xil_printf( "Color Filter Array Interpolation (CFA) Initialization ...\n\r" );
   CFA_Reset( pDemo->uBaseAddr_CFA );
   CFA_ClearReset( pDemo->uBaseAddr_CFA );
   CFA_Enable( pDemo->uBaseAddr_CFA );
   CFA_RegUpdateDisable( pDemo->uBaseAddr_CFA );
   CFA_WriteReg( pDemo->uBaseAddr_CFA, CFA_BAYER_PHASE, 0 );
   CFA_RegUpdateEnable( pDemo->uBaseAddr_CFA );
   xil_printf("\tCFA done\r\n");
#endif

//#if defined(XPAR_DPC_NUM_INSTANCES)
#if defined(XPAR_DPC_0_BASEADDR)
   xil_printf( "Defect Pixel Correction (DPC) Initialization ...\n\r" );
   DPC_Reset( pDemo->uBaseAddr_DPC );
   DPC_ClearReset( pDemo->uBaseAddr_DPC );
   DPC_Enable( pDemo->uBaseAddr_DPC );
   DPC_RegUpdateDisable( pDemo->uBaseAddr_DPC );
   DPC_WriteReg( pDemo->uBaseAddr_DPC, DPC_THRESH_PIXEL_AGE, 100 );
   DPC_RegUpdateEnable( pDemo->uBaseAddr_DPC );
   xil_printf("\tDPC done\r\n");
#endif

   xil_printf("\n\r");
   xil_printf( "Done\n\r" );
   xil_printf("\n\r");

   sleep(1);
  }

   return 0;
}
