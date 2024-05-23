#!/usr/sbin/dtrace -s

pid$target:cub3D:draw_sprite:entry
{
    self->start = timestamp;
}

pid$target:cub3D:draw_sprite:return
/self->start/
{
    printf("%s took %d ns\n", probefunc, timestamp - self->start);
    self->start = 0;
}
