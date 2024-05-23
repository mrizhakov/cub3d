#!/usr/sbin/dtrace -s

pid$target:cub3D:sprites_calculations:entry
{
    self->start = timestamp;
}

pid$target:cub3D:sprites_calculations:return
/self->start/
{
    printf("%s took %d ns\n", probefunc, timestamp - self->start);
    self->start = 0;
}
