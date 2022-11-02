//
// watch model in mm
//
e = 0.1;
$fn = 48;

$t = 0;

dpcb_wid = 33.5;
dpcb_hgt = 48.3;
dpcb_thk = 1.6;
dpcb_sol = 6.0;			/* standoff len */
dpcb_sod = 5.0;			/* standoff dia */

mm = 25.4;

conn_wid = 20;
conn_hgt = 6.1;
conn_thk = 5.3;

module conn() {
     translate( [-conn_wid/2, -conn_hgt/2, -conn_thk])
	  color("white")
	  cube( [conn_wid, conn_hgt, conn_thk]);
}

// waveshare 1.54 inch module
module display() {
     translate( [-dpcb_wid/2, -dpcb_hgt/2, 0]) {
	  color("darkgreen")
	       cube( [dpcb_wid, dpcb_hgt, dpcb_thk]);   // PCB
	  // display module
	  translate( [1.2, 5.3, 1.6]) {
	       color("silver")
	       cube( [31, 37.3, 1.2]);
	       // active region
	       color("white")
	       translate( [1.5, 0.5, 1.2])
		    cube( [28, 28, 0.2]);
	  }
	  // connector
	  translate( [pcb_wid/2, conn_hgt/2, 0])
	       conn();
	  // standoffs
	  sox = dpcb_sod/2;	/* offset from PCB corner */
	  translate( [0, 0, -dpcb_sol]) {
	       $fn = 6;
	       translate( [sox, sox, 0]) cylinder( h=dpcb_sol, d=dpcb_sod);
	       translate( [dpcb_wid-sox, sox, 0]) cylinder( h=dpcb_sol, d=dpcb_sod);
	       translate( [sox, dpcb_hgt-sox, 0]) cylinder( h=dpcb_sol, d=dpcb_sod);
	       translate( [dpcb_wid-sox, dpcb_hgt-sox, 0]) cylinder( h=dpcb_sol, d=dpcb_sod);
	  }
	  // components on back
	  comp_hgt = 2.5;
	  translate( [4, 5, -comp_hgt])
	       % cube( [25, 41, comp_hgt]);
     }
}

// SOP14 for R2025S
// rtc_wid = 10;
// rtc_hgt = 5;
// rtc_pins = 7.4;
// rtc_thk = 3.2;

// DS1339 in 8-TSSOP
rtc_wid = 3;
rtc_hgt = 3;
rtc_pins_wid = 5.0;
rtc_pins_hgt = 2.3;
rtc_thk = 1.1;

module rtc() {
     color("black")
	  translate( [-rtc_wid/2, -rtc_hgt/2, 0])
	       cube( [rtc_wid, rtc_hgt, rtc_thk]);
     color("silver")
	  translate( [-rtc_pins_wid/2, -rtc_pins_hgt/2, 0])
	       cube( [rtc_pins_wid, rtc_pins_hgt, 0.1]);
}
     
// 100mAh Lipo battery
lp_wid = 14;
lp_len = 18;
lp_thk = 7;

module lipo() {
     translate( [-lp_wid/2, -lp_len/2, 0])
	  color("orange")
	  cube( [lp_wid, lp_len, lp_thk]);
}



bh_wid = 15.3;
bh_hgt = 9.5;
bh_thk = 3.6;

// coin cell battery
module batt() {
     // Linx CR1216 SMT battery holder
     color("#303030") // holder outline
	  translate( [-bh_wid/2, -bh_hgt/2, 0])
	  cube( [bh_wid, bh_hgt, bh_thk]);
     color("silver")  // battery
	  cylinder( d=12, h=1.6);
     color("silver") { // solder pads/tabs
	  translate( [-8.9, -2.5, 0])
	       cube( [2.5, 5.1, 0.1]);
	  translate( [8.9-2.5, -2.5, 0])
	       cube( [2.5, 5.1, 0.1]);
     }
}


// nRF24
// wf_wid = 14.3;
// wf_hgt = 24.8;
// wf_thk = 4;

// RFM69
wf_wid = 20;			/* measured from photo */
wf_hgt = 20;
wf_thk = 3.2;			/* just a guess */

module wf() {
     translate( [-wf_wid/2, -wf_hgt/2, 0])
	  color("red")
	  cube( [wf_wid, wf_hgt, wf_thk]);
}


module sw( a) {
     rotate( [90, 180, 90+a])
	  color("silver")
     import("Unnamed-EVQP4KB3Q.3mf");
}

pcb_wid = dpcb_wid;
pcb_hgt = dpcb_hgt;
pcb_thk = dpcb_thk;

// Lipo position for cutout etc
lp_x = pcb_wid/2;
lp_y = 7.5;
lp_z = 1+pcb_thk-lp_thk;

lp_gap = 1.0;			// gap around Lipo

module pcb() {
     translate( [-pcb_wid/2, -pcb_hgt/2, 0]) {
	  color("blue") {
	       difference() {
		    cube( [pcb_wid, pcb_hgt, pcb_thk]); // board
		    translate( [lp_x, lp_y, -e])        // Lipo cutout
			 rotate( [0, 0, 90])	 // rotate same as Lipo
			 translate( [-lp_wid/2-lp_gap, -lp_len/2-lp_gap, 0])
			 cube( [lp_wid+2*lp_gap, lp_len+2*lp_gap, pcb_thk+2*e]);
	       }
	  }
     
	  // MCU
	  translate( [pcb_wid/2, 35, pcb_thk])  import("qfp64.stl");
	  // RTC
//	  translate( [pcb_wid/2, pcb_hgt-27.5, 0]) rotate( [0, 180, 0]) rtc();
	  translate( [pcb_wid/2, pcb_hgt-27.5, pcb_thk]) rtc();	  

	  // switches
	  translate( [0, 0, -pcb_thk]) {
	       translate( [5, 0, 0]) sw(270);
	       translate( [pcb_wid-5, 0, 0]) sw(270);
	       translate( [3, pcb_hgt, 0]) sw(90);
	       translate( [pcb_wid-3, pcb_hgt, 0]) sw(90);
	  }

	  // radio
	  translate( [pcb_wid/2, pcb_hgt-18, 0])
	       rotate( [0, 180, 90]) wf();

	  // battery
	  translate( [lp_x, lp_y, lp_z])
	       rotate( [0, 0, 90])
	       lipo();
     }
}

module guts() {
//     display();
     rotate( [180, 0, 0])  translate( [0, 0, dpcb_sol])  pcb();     

// for animation     
//     rotate( [180, 0, 0])  translate( [0, 0, pcb_thk+1.5+(1-$t)*5])  pcb();
}


//
// case
//

case_gap = 0.5;
case_wall = 1;

// case interior
case_wid = max( dpcb_wid, pcb_wid);
case_hgt = max( dpcb_hgt, pcb_hgt);
case_thk = 9;

// case exterior
case_ext = 2*case_gap+2*case_wall;
case_ewid = case_wid+case_ext;
case_ehgt = case_hgt+case_ext;
case_ethk = case_thk+case_ext;

// vertical offset for rendering
case_shift = 9;

module case() {
     // this is the inside volume with no gap
     //      translate( [-case_wid/2, -case_hgt/2, -case_shift])
     // %	  cube( [case_wid, case_hgt, case_thk]);

     translate( [-case_wid/2-case_gap-case_wall,
		 -case_hgt/2-case_gap-case_wall,
		 -case_shift-case_gap-case_wall ]) {

	  difference() {
	       // outer case, for now just rectilinear
	       cube( [case_ewid, case_ehgt, case_ethk]);
	       // interior
	       translate( [case_wall, case_wall, case_wall])
		    cube( [case_wid+2*case_gap,
			   case_hgt+2*case_gap,
			   case_thk+2*case_gap+5]);
	  }

     }
}


guts();
// % case();

echo("Case L/W/H = ", case_ewid, ", ", case_ehgt, ", ", case_ethk);
