#!/usr/sbin/dtrace -s

pid$target:cub3D::entry
{
    self->start = timestamp;
}

pid$target:cub3D::return
/self->start/
{
    printf("%s took %d ns\n", probefunc, timestamp - self->start);
    self->start = 0;
}
