 /**
  *************************************************************************
  * @file      blink.s
  * @author    Millenium Robotics
  * @date	   06.10.2022 (Thursday)
  * @brief     Assembly for a STM32L073rz board
  *				(cortex-m0+, thumb2 set instruction)
  *            This module performs:
  *				- init a led
  *				- toggles it
  *********************************************************************************
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  ********************************************************************************/

  .syntax unified
  .cpu cortex-m0plus
  .fpu softvfp
  .thumb

   .include "startup_stm32l073xx.s"
   .include "stm32l073rz.inc"

.section .data
    .set Iterations, 1000000

.section .text
.type Main, %function
.global Main
Main:
	BL Clk_Enable
	BL Led_Init
	LDR r5, =5				      		@ Number of LED flashes.
	BL Blink
	b .
@==============================================================
.type Clk_Enable, %function
Clk_Enable:
		LDR  R1, =RCC_IOPENR
		LDR	 R0, [R1]
		ORR  R0, R0, #IOPAEN					 @ enable gpioa
		STR  R0, [R1]	   			    		 @ clock
		BX   LR

@==============================================================
.type Led_Init, %function
Led_Init:
		LDR  R1, =GPIOA_MODER
		LDR	 R0, [R1]
		ORR	 R0, R0, #GPIOx_MODER_MODE0_OUTPUT	  @ output
		STR  R0, [R1]

		LDR  R1, =GPIOA_OTYPER
		LDR	 R0, [R1]
		ORR	 R0, R0, #GPIOx_OTYPER_OTx_PUSH_PULL  @ no open drain
		STR  R0, [R1]

		LDR  R1, =GPIOA_PUPDR				      @ no pull-down
		LDR	 R0, [R1]
		ORR	 R0, R0, #GPIOx_PUPDR_PUPDx_NO_PUPD   @ no pull-up
		STR  R0, [R1]

		LDR  R1, =GPIOA_OSPEEDR
		LDR	 R0, [R1]
		ORR  R0, R0, #GPIOx_OSPEEDR_OSPEED0_MEDIUM @ medium speed
		STR	 R0, [R1]
		BX   LR

@==============================================================
.type Led_On, %function
Led_On:
		LDR  R1, =GPIOA_BSRR
		LDR  R0, =GPIOx_BSRR_BS0  @ set pin high
		STR	 R0, [R1]
		BX	 LR

@==============================================================
.type Toggle, %function
Toggle:
		LDR  R1, =GPIOA_BSRR
		LDR  R2, =GPIOx_BSRR_BR0 @ reset pin
		STR	 R2, [R1]
		BX	 LR

@==============================================================
.type Delay, %function
Delay:
		LDR	 R4, =Iterations 	@ wait some time
     1: SUBS R4, #1				@ decrement it and set Z flag
        BNE  1b
        BX   LR
@==============================================================
.type Blink, %function
Blink:
 	push { LR }
	Loop:
		BL   Led_On			 	@ toggle Led
	    BL   Delay 				@ jump to delay till it is zero
		BL	 Toggle
		BL   Delay

		B	 Loop				@ infinite loop
	pop { LR }
	BX	LR
