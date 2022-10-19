//
// watch model in mm
//
e = 0.1;
$fn = 48;

dpcb_wid = 31.8;
dpcb_hgt = 48;
dpcb_thk = 1.6;

mm = 25.4;

conn_thk = 0.1*mm;
conn_pin = 0.64;
conn_plen = 8.5;

module pin() {
     translate( [ -conn_pin/2, -conn_pin/2, -conn_plen])
	  color("gold")
	  cube( [conn_pin, conn_pin, conn_plen]);
}

module conn() {
     translate( [-0.2*mm, -0.05*mm, -conn_thk]) {
     color("black")
	  cube([0.4*mm, 0.2*mm, conn_thk]);
     }
     for( x=[0:3]) {
	  for( y=[0:1]) {
	       translate( [ mm*(-0.15+0.1*x), mm*(0.1*y), 0])  pin();
	  }
     }
}

module display() {
     translate( [-dpcb_wid/2, -dpcb_hgt/2, 0]) {
	  color("darkgreen")
	       cube( [dpcb_wid, dpcb_hgt, dpcb_thk]);   // PCB
	  translate( [2.4, 13.26, 1.6])
	       color("white")
	       cube( [27, 27, 1.18]);
	  // now to center of connector
	  translate( [dpcb_wid/2, dpcb_hgt-(7.74/2), 0]) {
	       conn();
	  }
     }
}

// SOP14 for R2025S
rtc_wid = 10;
rtc_hgt = 5;
rtc_pins = 7.4;
rtc_thk = 3.2;

module rtc() {
     color("black")
	  translate( [-rtc_wid/2, -rtc_hgt/2, 0])
	       cube( [rtc_wid, rtc_hgt, rtc_thk]);
     color("silver")
	  translate( [-rtc_pins/2, -rtc_pins/2, 0])
	       cube( [rtc_pins, rtc_pins, 0.1]);
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


wf_wid = 14.3;
wf_hgt = 24.8;
wf_thk = 4;


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
lp_y = pcb_hgt-8;
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
	  translate( [pcb_wid/3, pcb_hgt/3, pcb_thk])  import("qfp64.stl");
	  // RTC
//     translate( [pcb_wid-6, pcb_hgt/3, pcb_thk])  rotate( [0, 0, 90]) rtc();
	  translate( [pcb_wid/2, pcb_hgt/2+3, 0]) rotate( [0, 180, 0]) rtc();

	  translate( [0, 0, -pcb_thk]) {
	       translate( [0, 10, 0]) sw(180);
	       translate( [0, 25, 0]) sw(180);
	  }
	  translate( [pcb_wid, 0, -pcb_thk]) {
	       translate( [0, 10, 0]) sw(0);
	       translate( [0, 25, 0]) sw(0);
	  }

	  translate( [pcb_wid/2, 15, 0])
	       rotate( [0, 180, 90]) wf();

	  translate( [lp_x, lp_y, lp_z])
	       rotate( [0, 0, 90])
	       lipo();
     }
}

module guts() {
     display();
     // rotate( [180, 0, 0])  translate( [0, -pcb_hgt, pcb_thk+1.5+(1-$t)*5])  pcb();
     rotate( [180, 0, 0])  translate( [0, 0, pcb_thk+1.5+(1-$t)*5])  pcb();
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
% case();

echo("Case L/W/H = ", case_ewid, ", ", case_ehgt, ", ", case_ethk);
