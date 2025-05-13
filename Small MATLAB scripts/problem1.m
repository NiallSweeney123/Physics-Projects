C=1.3e-6;
f=1000;
omega=2*pi*f;
%Variables are set.
ZC=-(1i/(omega*C));
%Complex impedance of a capacitor is calculated using the set variables.
L=0.0056;
ZL=1i*omega*L;
%Complex impedance of an inductor is calculated using the set variables.
R=100;
ZT=R+ZC+ZL;
Zmag=abs(ZT);
Zphi=angle(ZT);
%The magnitude and phase angle of ZT is calculated
x=linspace(100,100000,1000);
w=2*pi*x;
zc=-(1i./(w*C));
zl=1i*w*L;
zt=R+zc+zl;
y=abs(zt);
%The equations to calculate the total complex impedance are carried out
%then the magnitude of the complex impedance is calculated and used as the
%y-axis for the plot.
loglog(x,y,'LineWidth',1)
%The graph is plotted with logarithmic scales.
xlabel('Frequency(Hz)','FontSize',15)
ylabel('Magnitude of Impedance','FontSize',15)
title('Plot of frequency and magnitude of impedance from 100Hz to 100kHz')
%The x and y labels are inserted along with the title for the plot.
r=1/(2*pi*sqrt(L*C));
%The resonance frequency is calculated.
w2=2*pi*r;
zc2=-(1i./(w2*C));
zl2=1i*w2*L;
zt2=R+zc2+zl2;
y2=abs(zt2);
%The magnitude of impedance is calculate for the resonance frequency.
hold on
loglog(r,y2,'x','MarkerSize',14)
%The marker is then plotted with a red cross with a size of 14.
savefig('Figure1')

