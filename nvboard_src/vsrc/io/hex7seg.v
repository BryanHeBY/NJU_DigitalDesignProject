module hex7seg( //bcd码（16进制）转七段数码管输出模块
	input en,
	input  [3:0] b,
	output reg [6:0] h
	);

    always @(*) begin
		if(en) begin
        case(b)
            0 : h = 7'b1000000;
            1 : h = 7'b1111001;
            2 : h = 7'b0100100;
            3 : h = 7'b0110000;
            4 : h = 7'b0011001;
            5 : h = 7'b0010010;
            6 : h = 7'b0000010;
            7 : h = 7'b1111000;
            8 : h = 7'b0000000;
            9 : h = 7'b0010000;
            10 : h = 7'b0001000;
            11 : h = 7'b0000011;
            12 : h = 7'b1000110;
            13 : h = 7'b0100001;
            14 : h = 7'b0000110;
            15 : h = 7'b0001110;
            default : h = 7'b1111111;
        endcase 
		end
		else h = 7'b1111111;
    end
	 
	 
endmodule 