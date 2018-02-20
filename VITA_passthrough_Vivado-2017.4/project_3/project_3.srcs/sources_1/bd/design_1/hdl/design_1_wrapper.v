//Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
//Date        : Fri Feb 16 14:40:24 2018
//Host        : lkp-s002 running 64-bit major release  (build 9200)
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
   (DDR_addr,
    DDR_ba,
    DDR_cas_n,
    DDR_ck_n,
    DDR_ck_p,
    DDR_cke,
    DDR_cs_n,
    DDR_dm,
    DDR_dq,
    DDR_dqs_n,
    DDR_dqs_p,
    DDR_odt,
    DDR_ras_n,
    DDR_reset_n,
    DDR_we_n,
    FIXED_IO_ddr_vrn,
    FIXED_IO_ddr_vrp,
    FIXED_IO_mio,
    FIXED_IO_ps_clk,
    FIXED_IO_ps_porb,
    FIXED_IO_ps_srstb,
    fmc_imageon_iic_rst_n,
    fmc_imageon_iic_scl_io,
    fmc_imageon_iic_sda_io,
    hdmio_io_clk,
    hdmio_io_data,
    hdmio_io_spdif,
    vita_clk,
    vita_io_clk_out_n,
    vita_io_clk_out_p,
    vita_io_clk_pll,
    vita_io_data_n,
    vita_io_data_p,
    vita_io_monitor,
    vita_io_reset_n,
    vita_io_spi_miso,
    vita_io_spi_mosi,
    vita_io_spi_sclk,
    vita_io_spi_ssel_n,
    vita_io_sync_n,
    vita_io_sync_p,
    vita_io_trigger);
  inout [14:0]DDR_addr;
  inout [2:0]DDR_ba;
  inout DDR_cas_n;
  inout DDR_ck_n;
  inout DDR_ck_p;
  inout DDR_cke;
  inout DDR_cs_n;
  inout [3:0]DDR_dm;
  inout [31:0]DDR_dq;
  inout [3:0]DDR_dqs_n;
  inout [3:0]DDR_dqs_p;
  inout DDR_odt;
  inout DDR_ras_n;
  inout DDR_reset_n;
  inout DDR_we_n;
  inout FIXED_IO_ddr_vrn;
  inout FIXED_IO_ddr_vrp;
  inout [53:0]FIXED_IO_mio;
  inout FIXED_IO_ps_clk;
  inout FIXED_IO_ps_porb;
  inout FIXED_IO_ps_srstb;
  output [0:0]fmc_imageon_iic_rst_n;
  inout fmc_imageon_iic_scl_io;
  inout fmc_imageon_iic_sda_io;
  output hdmio_io_clk;
  output [15:0]hdmio_io_data;
  output hdmio_io_spdif;
  input vita_clk;
  input vita_io_clk_out_n;
  input vita_io_clk_out_p;
  output vita_io_clk_pll;
  input [3:0]vita_io_data_n;
  input [3:0]vita_io_data_p;
  input [1:0]vita_io_monitor;
  output vita_io_reset_n;
  input vita_io_spi_miso;
  output vita_io_spi_mosi;
  output vita_io_spi_sclk;
  output vita_io_spi_ssel_n;
  input vita_io_sync_n;
  input vita_io_sync_p;
  output [2:0]vita_io_trigger;

  wire [14:0]DDR_addr;
  wire [2:0]DDR_ba;
  wire DDR_cas_n;
  wire DDR_ck_n;
  wire DDR_ck_p;
  wire DDR_cke;
  wire DDR_cs_n;
  wire [3:0]DDR_dm;
  wire [31:0]DDR_dq;
  wire [3:0]DDR_dqs_n;
  wire [3:0]DDR_dqs_p;
  wire DDR_odt;
  wire DDR_ras_n;
  wire DDR_reset_n;
  wire DDR_we_n;
  wire FIXED_IO_ddr_vrn;
  wire FIXED_IO_ddr_vrp;
  wire [53:0]FIXED_IO_mio;
  wire FIXED_IO_ps_clk;
  wire FIXED_IO_ps_porb;
  wire FIXED_IO_ps_srstb;
  wire [0:0]fmc_imageon_iic_rst_n;
  wire fmc_imageon_iic_scl_i;
  wire fmc_imageon_iic_scl_io;
  wire fmc_imageon_iic_scl_o;
  wire fmc_imageon_iic_scl_t;
  wire fmc_imageon_iic_sda_i;
  wire fmc_imageon_iic_sda_io;
  wire fmc_imageon_iic_sda_o;
  wire fmc_imageon_iic_sda_t;
  wire hdmio_io_clk;
  wire [15:0]hdmio_io_data;
  wire hdmio_io_spdif;
  wire vita_clk;
  wire vita_io_clk_out_n;
  wire vita_io_clk_out_p;
  wire vita_io_clk_pll;
  wire [3:0]vita_io_data_n;
  wire [3:0]vita_io_data_p;
  wire [1:0]vita_io_monitor;
  wire vita_io_reset_n;
  wire vita_io_spi_miso;
  wire vita_io_spi_mosi;
  wire vita_io_spi_sclk;
  wire vita_io_spi_ssel_n;
  wire vita_io_sync_n;
  wire vita_io_sync_p;
  wire [2:0]vita_io_trigger;

  design_1 design_1_i
       (.DDR_addr(DDR_addr),
        .DDR_ba(DDR_ba),
        .DDR_cas_n(DDR_cas_n),
        .DDR_ck_n(DDR_ck_n),
        .DDR_ck_p(DDR_ck_p),
        .DDR_cke(DDR_cke),
        .DDR_cs_n(DDR_cs_n),
        .DDR_dm(DDR_dm),
        .DDR_dq(DDR_dq),
        .DDR_dqs_n(DDR_dqs_n),
        .DDR_dqs_p(DDR_dqs_p),
        .DDR_odt(DDR_odt),
        .DDR_ras_n(DDR_ras_n),
        .DDR_reset_n(DDR_reset_n),
        .DDR_we_n(DDR_we_n),
        .FIXED_IO_ddr_vrn(FIXED_IO_ddr_vrn),
        .FIXED_IO_ddr_vrp(FIXED_IO_ddr_vrp),
        .FIXED_IO_mio(FIXED_IO_mio),
        .FIXED_IO_ps_clk(FIXED_IO_ps_clk),
        .FIXED_IO_ps_porb(FIXED_IO_ps_porb),
        .FIXED_IO_ps_srstb(FIXED_IO_ps_srstb),
        .fmc_imageon_iic_rst_n(fmc_imageon_iic_rst_n),
        .fmc_imageon_iic_scl_i(fmc_imageon_iic_scl_i),
        .fmc_imageon_iic_scl_o(fmc_imageon_iic_scl_o),
        .fmc_imageon_iic_scl_t(fmc_imageon_iic_scl_t),
        .fmc_imageon_iic_sda_i(fmc_imageon_iic_sda_i),
        .fmc_imageon_iic_sda_o(fmc_imageon_iic_sda_o),
        .fmc_imageon_iic_sda_t(fmc_imageon_iic_sda_t),
        .hdmio_io_clk(hdmio_io_clk),
        .hdmio_io_data(hdmio_io_data),
        .hdmio_io_spdif(hdmio_io_spdif),
        .vita_clk(vita_clk),
        .vita_io_clk_out_n(vita_io_clk_out_n),
        .vita_io_clk_out_p(vita_io_clk_out_p),
        .vita_io_clk_pll(vita_io_clk_pll),
        .vita_io_data_n(vita_io_data_n),
        .vita_io_data_p(vita_io_data_p),
        .vita_io_monitor(vita_io_monitor),
        .vita_io_reset_n(vita_io_reset_n),
        .vita_io_spi_miso(vita_io_spi_miso),
        .vita_io_spi_mosi(vita_io_spi_mosi),
        .vita_io_spi_sclk(vita_io_spi_sclk),
        .vita_io_spi_ssel_n(vita_io_spi_ssel_n),
        .vita_io_sync_n(vita_io_sync_n),
        .vita_io_sync_p(vita_io_sync_p),
        .vita_io_trigger(vita_io_trigger));
  IOBUF fmc_imageon_iic_scl_iobuf
       (.I(fmc_imageon_iic_scl_o),
        .IO(fmc_imageon_iic_scl_io),
        .O(fmc_imageon_iic_scl_i),
        .T(fmc_imageon_iic_scl_t));
  IOBUF fmc_imageon_iic_sda_iobuf
       (.I(fmc_imageon_iic_sda_o),
        .IO(fmc_imageon_iic_sda_io),
        .O(fmc_imageon_iic_sda_i),
        .T(fmc_imageon_iic_sda_t));
endmodule
