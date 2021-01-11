.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

glabel pause_textbox_draw_contents
/* 1368B0 80243570 27BDFFC8 */  addiu     $sp, $sp, -0x38
/* 1368B4 80243574 AFB20020 */  sw        $s2, 0x20($sp)
/* 1368B8 80243578 3C128027 */  lui       $s2, %hi(D_80270108)
/* 1368BC 8024357C 8E520108 */  lw        $s2, %lo(D_80270108)($s2)
/* 1368C0 80243580 AFB60030 */  sw        $s6, 0x30($sp)
/* 1368C4 80243584 8FB60048 */  lw        $s6, 0x48($sp)
/* 1368C8 80243588 AFB30024 */  sw        $s3, 0x24($sp)
/* 1368CC 8024358C 00A0982D */  daddu     $s3, $a1, $zero
/* 1368D0 80243590 AFB40028 */  sw        $s4, 0x28($sp)
/* 1368D4 80243594 00C0A02D */  daddu     $s4, $a2, $zero
/* 1368D8 80243598 AFB5002C */  sw        $s5, 0x2c($sp)
/* 1368DC 8024359C 00E0A82D */  daddu     $s5, $a3, $zero
/* 1368E0 802435A0 AFBF0034 */  sw        $ra, 0x34($sp)
/* 1368E4 802435A4 AFB1001C */  sw        $s1, 0x1c($sp)
/* 1368E8 802435A8 12400088 */  beqz      $s2, .L802437CC
/* 1368EC 802435AC AFB00018 */   sw       $s0, 0x18($sp)
/* 1368F0 802435B0 3C118027 */  lui       $s1, %hi(D_80270110)
/* 1368F4 802435B4 26310110 */  addiu     $s1, $s1, %lo(D_80270110)
/* 1368F8 802435B8 8E220000 */  lw        $v0, ($s1)
/* 1368FC 802435BC 1040000B */  beqz      $v0, .L802435EC
/* 136900 802435C0 02752821 */   addu     $a1, $s3, $s5
/* 136904 802435C4 24A5FFFC */  addiu     $a1, $a1, -4
/* 136908 802435C8 3C108027 */  lui       $s0, %hi(gPauseMenuCommonIconIDs)
/* 13690C 802435CC 261000E8 */  addiu     $s0, $s0, %lo(gPauseMenuCommonIconIDs)
/* 136910 802435D0 8E040004 */  lw        $a0, 4($s0)
/* 136914 802435D4 0C051261 */  jal       set_icon_render_pos
/* 136918 802435D8 26860004 */   addiu    $a2, $s4, 4
/* 13691C 802435DC 8E040004 */  lw        $a0, 4($s0)
/* 136920 802435E0 0C0511F8 */  jal       draw_icon_2
/* 136924 802435E4 00000000 */   nop      
/* 136928 802435E8 8E220000 */  lw        $v0, ($s1)
.L802435EC:
/* 13692C 802435EC 3C038027 */  lui       $v1, %hi(D_8027010C)
/* 136930 802435F0 8C63010C */  lw        $v1, %lo(D_8027010C)($v1)
/* 136934 802435F4 0043102A */  slt       $v0, $v0, $v1
/* 136938 802435F8 1040000B */  beqz      $v0, .L80243628
/* 13693C 802435FC 02752821 */   addu     $a1, $s3, $s5
/* 136940 80243600 24A5FFFC */  addiu     $a1, $a1, -4
/* 136944 80243604 3C108027 */  lui       $s0, %hi(gPauseMenuCommonIconIDs)
/* 136948 80243608 261000E8 */  addiu     $s0, $s0, %lo(gPauseMenuCommonIconIDs)
/* 13694C 8024360C 02963021 */  addu      $a2, $s4, $s6
/* 136950 80243610 8E040008 */  lw        $a0, 8($s0)
/* 136954 80243614 0C051261 */  jal       set_icon_render_pos
/* 136958 80243618 24C6FFFC */   addiu    $a2, $a2, -4
/* 13695C 8024361C 8E040008 */  lw        $a0, 8($s0)
/* 136960 80243620 0C0511F8 */  jal       draw_icon_2
/* 136964 80243624 00000000 */   nop      
.L80243628:
/* 136968 80243628 0240202D */  daddu     $a0, $s2, $zero
/* 13696C 8024362C 3C11800A */  lui       $s1, %hi(gMasterGfxPos)
/* 136970 80243630 2631A66C */  addiu     $s1, $s1, %lo(gMasterGfxPos)
/* 136974 80243634 2665000A */  addiu     $a1, $s3, 0xa
/* 136978 80243638 3C02E700 */  lui       $v0, 0xe700
/* 13697C 8024363C 3C10ED00 */  lui       $s0, 0xed00
/* 136980 80243640 8E280000 */  lw        $t0, ($s1)
/* 136984 80243644 3C068027 */  lui       $a2, %hi(D_80270114)
/* 136988 80243648 8CC60114 */  lw        $a2, %lo(D_80270114)($a2)
/* 13698C 8024364C 3C014080 */  lui       $at, 0x4080
/* 136990 80243650 44812000 */  mtc1      $at, $f4
/* 136994 80243654 0100182D */  daddu     $v1, $t0, $zero
/* 136998 80243658 25080008 */  addiu     $t0, $t0, 8
/* 13699C 8024365C 02863023 */  subu      $a2, $s4, $a2
/* 1369A0 80243660 AE280000 */  sw        $t0, ($s1)
/* 1369A4 80243664 AC620000 */  sw        $v0, ($v1)
/* 1369A8 80243668 26620001 */  addiu     $v0, $s3, 1
/* 1369AC 8024366C 44821000 */  mtc1      $v0, $f2
/* 1369B0 80243670 00000000 */  nop       
/* 1369B4 80243674 468010A0 */  cvt.s.w   $f2, $f2
/* 1369B8 80243678 AC600004 */  sw        $zero, 4($v1)
/* 1369BC 8024367C 25030008 */  addiu     $v1, $t0, 8
/* 1369C0 80243680 46041082 */  mul.s     $f2, $f2, $f4
/* 1369C4 80243684 00000000 */  nop       
/* 1369C8 80243688 26820001 */  addiu     $v0, $s4, 1
/* 1369CC 8024368C 44820000 */  mtc1      $v0, $f0
/* 1369D0 80243690 00000000 */  nop       
/* 1369D4 80243694 46800020 */  cvt.s.w   $f0, $f0
/* 1369D8 80243698 02751021 */  addu      $v0, $s3, $s5
/* 1369DC 8024369C 2442FFFF */  addiu     $v0, $v0, -1
/* 1369E0 802436A0 46040002 */  mul.s     $f0, $f0, $f4
/* 1369E4 802436A4 00000000 */  nop       
/* 1369E8 802436A8 AE230000 */  sw        $v1, ($s1)
/* 1369EC 802436AC 4600118D */  trunc.w.s $f6, $f2
/* 1369F0 802436B0 44033000 */  mfc1      $v1, $f6
/* 1369F4 802436B4 00000000 */  nop       
/* 1369F8 802436B8 30630FFF */  andi      $v1, $v1, 0xfff
/* 1369FC 802436BC 00031B00 */  sll       $v1, $v1, 0xc
/* 136A00 802436C0 4600018D */  trunc.w.s $f6, $f0
/* 136A04 802436C4 44073000 */  mfc1      $a3, $f6
/* 136A08 802436C8 00000000 */  nop       
/* 136A0C 802436CC 30E70FFF */  andi      $a3, $a3, 0xfff
/* 136A10 802436D0 00F03825 */  or        $a3, $a3, $s0
/* 136A14 802436D4 44821000 */  mtc1      $v0, $f2
/* 136A18 802436D8 00000000 */  nop       
/* 136A1C 802436DC 468010A0 */  cvt.s.w   $f2, $f2
/* 136A20 802436E0 00671825 */  or        $v1, $v1, $a3
/* 136A24 802436E4 46041082 */  mul.s     $f2, $f2, $f4
/* 136A28 802436E8 00000000 */  nop       
/* 136A2C 802436EC 02961021 */  addu      $v0, $s4, $s6
/* 136A30 802436F0 2442FFFF */  addiu     $v0, $v0, -1
/* 136A34 802436F4 44820000 */  mtc1      $v0, $f0
/* 136A38 802436F8 00000000 */  nop       
/* 136A3C 802436FC 46800020 */  cvt.s.w   $f0, $f0
/* 136A40 80243700 240700FF */  addiu     $a3, $zero, 0xff
/* 136A44 80243704 46040002 */  mul.s     $f0, $f0, $f4
/* 136A48 80243708 00000000 */  nop       
/* 136A4C 8024370C AD030000 */  sw        $v1, ($t0)
/* 136A50 80243710 4600118D */  trunc.w.s $f6, $f2
/* 136A54 80243714 44023000 */  mfc1      $v0, $f6
/* 136A58 80243718 00000000 */  nop       
/* 136A5C 8024371C 30420FFF */  andi      $v0, $v0, 0xfff
/* 136A60 80243720 00021300 */  sll       $v0, $v0, 0xc
/* 136A64 80243724 4600018D */  trunc.w.s $f6, $f0
/* 136A68 80243728 44033000 */  mfc1      $v1, $f6
/* 136A6C 8024372C 00000000 */  nop       
/* 136A70 80243730 30630FFF */  andi      $v1, $v1, 0xfff
/* 136A74 80243734 00431025 */  or        $v0, $v0, $v1
/* 136A78 80243738 AD020004 */  sw        $v0, 4($t0)
/* 136A7C 8024373C 2402000A */  addiu     $v0, $zero, 0xa
/* 136A80 80243740 AFA20010 */  sw        $v0, 0x10($sp)
/* 136A84 80243744 0C04993B */  jal       draw_string
/* 136A88 80243748 AFA00014 */   sw       $zero, 0x14($sp)
/* 136A8C 8024374C 3C128027 */  lui       $s2, %hi(D_80270118)
/* 136A90 80243750 26520118 */  addiu     $s2, $s2, %lo(D_80270118)
/* 136A94 80243754 8E420000 */  lw        $v0, ($s2)
/* 136A98 80243758 1040001C */  beqz      $v0, .L802437CC
/* 136A9C 8024375C 3C040050 */   lui      $a0, 0x50
/* 136AA0 80243760 348403C0 */  ori       $a0, $a0, 0x3c0
/* 136AA4 80243764 2665FFFC */  addiu     $a1, $s3, -4
/* 136AA8 80243768 8E230000 */  lw        $v1, ($s1)
/* 136AAC 8024376C 26860010 */  addiu     $a2, $s4, 0x10
/* 136AB0 80243770 0060102D */  daddu     $v0, $v1, $zero
/* 136AB4 80243774 AC500000 */  sw        $s0, ($v0)
/* 136AB8 80243778 3C108027 */  lui       $s0, %hi(gPauseMenuCommonIconIDs)
/* 136ABC 8024377C 261000E8 */  addiu     $s0, $s0, %lo(gPauseMenuCommonIconIDs)
/* 136AC0 80243780 AC440004 */  sw        $a0, 4($v0)
/* 136AC4 80243784 8E04000C */  lw        $a0, 0xc($s0)
/* 136AC8 80243788 24630008 */  addiu     $v1, $v1, 8
/* 136ACC 8024378C 0C051261 */  jal       set_icon_render_pos
/* 136AD0 80243790 AE230000 */   sw       $v1, ($s1)
/* 136AD4 80243794 8E04000C */  lw        $a0, 0xc($s0)
/* 136AD8 80243798 0C0511FF */  jal       set_menu_icon_script
/* 136ADC 8024379C 8E450000 */   lw       $a1, ($s2)
/* 136AE0 802437A0 8E04000C */  lw        $a0, 0xc($s0)
/* 136AE4 802437A4 0C051280 */  jal       set_icon_flags
/* 136AE8 802437A8 3C052000 */   lui      $a1, 0x2000
/* 136AEC 802437AC 8E04000C */  lw        $a0, 0xc($s0)
/* 136AF0 802437B0 0C05128B */  jal       clear_icon_flags
/* 136AF4 802437B4 34058000 */   ori      $a1, $zero, 0x8000
/* 136AF8 802437B8 8E04000C */  lw        $a0, 0xc($s0)
/* 136AFC 802437BC 0C051308 */  jal       func_80144C20
/* 136B00 802437C0 3C053F80 */   lui      $a1, 0x3f80
/* 136B04 802437C4 0C0511F8 */  jal       draw_icon_2
/* 136B08 802437C8 8E04000C */   lw       $a0, 0xc($s0)
.L802437CC:
/* 136B0C 802437CC 8FBF0034 */  lw        $ra, 0x34($sp)
/* 136B10 802437D0 8FB60030 */  lw        $s6, 0x30($sp)
/* 136B14 802437D4 8FB5002C */  lw        $s5, 0x2c($sp)
/* 136B18 802437D8 8FB40028 */  lw        $s4, 0x28($sp)
/* 136B1C 802437DC 8FB30024 */  lw        $s3, 0x24($sp)
/* 136B20 802437E0 8FB20020 */  lw        $s2, 0x20($sp)
/* 136B24 802437E4 8FB1001C */  lw        $s1, 0x1c($sp)
/* 136B28 802437E8 8FB00018 */  lw        $s0, 0x18($sp)
/* 136B2C 802437EC 03E00008 */  jr        $ra
/* 136B30 802437F0 27BD0038 */   addiu    $sp, $sp, 0x38
