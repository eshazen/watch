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

pcb_wid = dpcb_wid;
pcb_hgt = dpcb_hgt;
pcb_thk = dpcb_thk;

module pcb() {
     color("blue")
     cube( [pcb_wid, pcb_hgt, pcb_thk]);
     translate( [pcb_wid/2, pcb_hgt/2, pcb_thk])
	  import("qfp64.stl");
}


display();
rotate( [180, 0, 0])
translate( [0, -pcb_hgt, pcb_thk+1.5])
pcb();


