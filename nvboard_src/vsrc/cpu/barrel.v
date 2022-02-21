module barrel(
    input [31:0] indata,
    input [4:0] shamt,
    input lr,
    input al,
    output [31:0] outdata
);

reg [31:0] sh_data [4:0];
wire hin;

assign hin = al ? indata[31] : 1'b0;
assign outdata = sh_data[4];

always @(*) begin
    if(lr)begin
        sh_data[0] = shamt[0] ? {indata[30:0], 1'd0} : indata;
        sh_data[1] = shamt[1] ? {sh_data[0][29:0], 2'd0} : sh_data[0];
        sh_data[2] = shamt[2] ? {sh_data[1][27:0], 4'd0} : sh_data[1];
        sh_data[3] = shamt[3] ? {sh_data[2][23:0], 8'd0} : sh_data[2];
        sh_data[4] = shamt[4] ? {sh_data[3][15:0], 16'd0} : sh_data[3];
    end
    else begin
        sh_data[0] = shamt[0] ? {{1{hin}}, indata[31:1]} : indata;
        sh_data[1] = shamt[1] ? {{2{hin}}, sh_data[0][31:2]} : sh_data[0];
        sh_data[2] = shamt[2] ? {{4{hin}}, sh_data[1][31:4]} : sh_data[1];
        sh_data[3] = shamt[3] ? {{8{hin}}, sh_data[2][31:8]} : sh_data[2];
        sh_data[4] = shamt[4] ? {{16{hin}}, sh_data[3][31:16]} : sh_data[3];
    end
end

endmodule
