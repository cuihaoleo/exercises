#!/usr/bin/env python3

import datetime as dt
import math
import operator
from math import degrees as deg
import matplotlib.pyplot as plt
from functools import reduce


# reduce an angle to 0~360 degrees
def map_to_360deg(ang):
    return ang - 360 * math.floor(ang/360)


# sine function with argument in angle
def sin(ang):
    return math.sin(math.radians(ang))


# cosine function with argument in angle
def cos(ang):
    return math.cos(math.radians(ang))


# a shortcut to the sum of parse(p[i,0]*p[i,1]*...) by i
def gracefulol(pairs, parse=lambda x: x):
    accu = 0
    for p in pairs:
        accu += parse(reduce(operator.mul, p))
    return parse(accu)


# calculate 6 astronomical parameters
def astro_params(time):

    def to_j1900_day(d):
        j1900 = dt.datetime(1899, 12, 31, 12, tzinfo=dt.timezone.utc)
        delta = d.timestamp() - j1900.timestamp()
        return delta / 86400.0

    # Julian century in J1900.0
    T = to_j1900_day(time) / 36525

    # Mean longitude of the Sun
    h = gracefulol([
            (279.69668, 1),
            (36000.76892, T),
            (0.00030, T*T)], map_to_360deg)
    # Mean longitude of Earth's perihelion
    ps = gracefulol([
            (281.22083, 1),
            (1.71902, T),
            (0.00045, T*T),
            (0.000003, T*T*T)], map_to_360deg)

    # Mean longitude of the Moon
    s = gracefulol([
            (270.43659, 1),
            (481267.89057, T),
            (0.00198, T*T),
            (0.000002, T*T*T)], map_to_360deg)
    # Mean longitude of the Moon's perihelion
    p = gracefulol([
            (334.32956, 1),
            (4069.03403, T),
            (0.01032, T*T),
            (-0.000001, T*T*T)], map_to_360deg)
    # Mean longitude of the Moon's ascending node
    N_ = gracefulol([
            (259.18328, 1),
            (1934.14201, T),
            (5.00208, T*T),
            (0.000002, T*T*T)], map_to_360deg)
    N = -N_

    return time, T, h, ps, s, p, N


def doo_factory(magic, magic_f, doo_code, phase_correct, time, loc):
    a, b, c, d, e, f = [i-5 for i in doo_code]
    a += 5

    w = gracefulol([
            (a, 14.4920521),
            (b, 0.5490165),
            (c, 0.0410686),
            (d, 0.0046418),
            (e, 0.0022064),
            (f, 0.0000020)])

    time, T, h, ps, s, p, N = astro_params(time)
    phi, L = loc
    tau = (time.timestamp() % 86400)*15/3600 + h - s + L
    phase = gracefulol([
                (phase_correct, 1),
                (a, tau), (b, s), (c, h),
                (d, p), (e, -N), (f, ps)], map_to_360deg)

    def doo(t):
        return magic * magic_f(phi) * cos(phase + w*t)

    return doo


def method1(time, loc):
    phi, L = loc

    C = 82.49
    d1 = lambda phi: C * cos(phi)**2
    d2 = lambda phi: C * sin(2*phi)

    factory = lambda a, b, c, d: doo_factory(a, b, c, d, time, loc)
    M2 = factory(0.90812, d1, b'\2\5\5\5\5\5', 180)
    S2 = factory(0.42358, d1, b'\2\7\3\5\5\5', 180)
    N2 = factory(0.17387, d1, b'\2\4\5\6\5\5', 180)
    K1 = factory(0.53050, d2, b'\1\6\5\5\5\5', -90)
    O1 = factory(0.37689, d2, b'\1\4\5\5\5\5', 90)

    return lambda t: M2(t) + S2(t) + N2(t) + K1(t) + O1(t)


def method2(d_o, loc):
    phi, L = loc

    def func(delta_hour):
        d = d_o + dt.timedelta(hours=delta_hour)
        d, T, h, ps, s, p, N = astro_params(d)

        cm_rm = gracefulol([
            (1, 1),
            (0.054501, cos(s-p)),
            (0.010025, cos(s-2*h+p)),
            (0.008249, cos(2*(s-h))),
            (0.002970, cos(2*(s-p)))])
        lmd_m = gracefulol([
            (1, s),
            (deg(0.109760), sin(s-p)),
            (deg(0.022236), sin(s-2*h+p)),
            (deg(0.011490), sin(2*(s-h))),
            (deg(0.003728), sin(2*(s-p)))], map_to_360deg)
        beta_m = gracefulol([
            (deg(0.089504), sin(s-N)),
            (deg(0.004897), sin(2*s-p-N)),
            (-deg(0.004847), sin(p-N)),
            (deg(0.003024), sin(s-2*h+N))], map_to_360deg)

        cs_rs = gracefulol([
            (1, 1),
            (0.016750, cos(h-ps)),
            (0.000280, cos(2*(h-ps))),
            (0.000005, cos(3*(h-ps)))])
        lmd_s = gracefulol([
            (1, h),
            (deg(0.016750), cos(h-ps)),
            (deg(0.000280), cos(2*(h-ps))),
            (deg(0.000005), cos(3*(h-ps)))], map_to_360deg)

        x = (d.timestamp() % 86400)*15/3600 + h + L - 180
        E = gracefulol([
            (23.452294, 1),
            (-0.0130125, T),
            (-0.0000016, T*T),
            (0.0000005, T*T*T)], map_to_360deg)

        cos_zm = sin(phi) * (
                     sin(E)*sin(lmd_m)*cos(beta_m) +
                     cos(E)*sin(beta_m)) + \
                 cos(phi) * (
                     cos(lmd_m)*cos(beta_m)*cos(x) +
                     sin(x) * (
                         cos(E)*sin(lmd_m)*cos(beta_m) +
                         -sin(E)*sin(beta_m)))
        d_gm = 54.993 * cm_rm**3 * (1-3*cos_zm**2) + \
                1.369 * cm_rm**4 * (3*cos_zm - 5*cos_zm**3)

        cos_zs = sin(phi) * sin(lmd_s)*sin(E) + \
                 cos(phi) * (
                     cos(lmd_s)*cos(x) +
                     sin(lmd_s)*sin(x)*cos(E))
        d_gs = 25.358 * cs_rs**3 * (1-3*cos_zs**2)

        return d_gm + d_gs

    return func


if __name__ == "__main__":
    time = dt.datetime(2015, 10, 15, 0)
    duration = 6*24
    location = (34.75, 113.63)

    m1 = method1(time, location)
    m2 = method2(time, location)

    ans1 = [m1(i) for i in range(duration)]
    ans2 = [m2(i) for i in range(duration)]

    plt1, = plt.plot(ans1, label="5 main components")
    plt2, = plt.plot(ans2, label="calc directly")
    plt.legend(handles=[plt1, plt2])
    plt.title("gravity tides in Zhengzhou "
              "(2015/10/15 00:00 ~ 2015/10/21 00:00 CST)")
    plt.xlabel("time / h")
    plt.ylabel("tide force / microgal")
    plt.show()
