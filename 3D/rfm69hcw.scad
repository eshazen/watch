
// RFM69HCW simple model

pcb_wid = 16;
pcb_len = 16;
pcb_thk = 1.0;
comp_hgt = 0.8;
pitch = 2.0;

hole_dia = 0.8;
pad_wid = 1.8;
pad_len = 1.2;

e = 0.1;

$fn = 32;


module part_at( x, y, wid, leng, thk) {
     translate( [x, y, pcb_thk])
	  color("black")
	  cube( [wid, leng, thk]);
}


module pcb() {
	  color("blue")
	       cube( [pcb_wid, pcb_len, pcb_thk]);

	  // pads
	  translate( [0, 1-pad_len/2, pcb_thk]) {
	       for( y=[0:2:14]) {
		    translate( [0, y, 0])
			 cube( [pad_wid, pad_len, e/2]);
		    translate( [pcb_wid-pad_wid, y, 0])
			 cube( [pad_wid, pad_len, e/2]);
	       }
	  }

	  // parts
	  part_at( 3, 10, 4, 4, 0.8);
	  for( x=[3:1.2:12]) {
	       part_at( x, 7, 1, 2, .8);
	       part_at( x, 4, 1, 2, .8);
	  }
}

translate( [-pcb_wid/2, -pcb_len/2, 0]) {

     difference() {
	  pcb();

	  // castllations
	  translate( [0, 1, -e]) {
	       for( y=[0:2:14]) {
		    translate( [0, y, 0]) {
			 cylinder( h=pcb_thk+2*e, d=hole_dia);
			 translate( [1.2, 0, 0])
			      cylinder( h=pcb_thk+2*e, d=hole_dia);
		    }
		    translate( [pcb_wid, y, 0]) {
			 cylinder( h=pcb_thk+2*e, d=hole_dia);
			 translate( [-1.2, 0, 0])
				    cylinder( h=pcb_thk+2*e, d=hole_dia);
		    }
	       }
	  }
     }

}
