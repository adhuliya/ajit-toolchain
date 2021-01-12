    ! enable tx
    sethi  %hi(0xffff3000), %g1
    or  %g1, 0x200, %g1
    or  %g0, 0x1, %g2	! ffff3200 <buffer_data+0xfffe31df>
    sta %g2, [%g1] 0x20
    lda [%g1] 0x20, %g3 ! g3 should contain 0x1 
    !
    or  %g1, 0x10, %g1
    or  %g0, 0x48, %g2
    stuba %g2, [%g1] 0x20 ! should transmit 'H' to console.
    or  %g0, 0x45, %g2
    stuba %g2, [%g1] 0x20 ! should transmit 'E' to console.
    or  %g0, 0x4c, %g2
    stuba %g2, [%g1] 0x20 ! should transmit 'L' to console.
    or  %g0, 0x50, %g2
    stuba %g2, [%g1] 0x20 ! should transmit 'P' to console.
    or  %g0, 0x0a, %g2
    stuba %g2, [%g1] 0x20 ! should transmit '\n' to console.
    !
    ta 0
    
