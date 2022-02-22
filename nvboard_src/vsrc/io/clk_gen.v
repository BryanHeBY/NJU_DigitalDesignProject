module clkgen (
    input clkin,
    input rst,
    input clken,
    output reg clkout
);
    
    parameter clk_freq = 1000;
    parameter countlimit = `CLK_FREQ/2/clk_freq;

    reg [31:0] clkcount;
    always @(posedge clkin) begin
        if(rst)begin
            clkcount <= 0;
            clkout <= 1'b0;
        end
        else begin
            if(clken)begin
                if(clkcount + 1 == countlimit)begin
                    clkcount <= 32'd0;
                    clkout <= ~clkout;
                end
                else begin
                    clkcount <= clkcount + 1;
                end
            end
        end
    end

endmodule

module clkcount (
    input clkin,
    output reg [31:0] clkcount
);
    
parameter clk_freq = 1000;
parameter countlimit = `CLK_FREQ/clk_freq;

reg [31:0] in_count;

initial begin
    in_count = 0;
    clkcount = 0;
end

always @(posedge clkin) begin
    if(in_count + 1 == countlimit)begin
        clkcount <= clkcount + 1;
        in_count <= 32'd0;
    end
    else begin
        in_count <= in_count + 1;
    end
end

endmodule
