##What is lunarcoin?

lunarcoin is a better version of Bitcoin using scrypt as a proof-of-work algorithm.

    	20 seconds block targets
    	subsidy halves in 840k blocks (~4 years)
    	~100 million total coins
   	64 coins per block
    	

Why we also say it's better than Litecoin, because lunarcoin has one of the fastest payouts. So you get very very fast you're money

##License

lunarcoin is released under the terms of the MIT license. See COPYING for more information or see http://opensource.org/licenses/MIT.

##Development process

Developers work in their own trees, then submit pull requests when they think their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the lunarcoin development team members simply pulls it.

If it is a more complicated or potentially controversial change, then the patch submitter will be asked to start a discussion (if they haven't already).

The patch will be accepted if there is broad consensus that it is a good thing. Developers should expect to rework and resubmit patches if the code doesn't match the project's coding conventions (see doc/coding.txt) or are controversial.

The master branch is regularly built and tested, but is not guaranteed to be completely stable. Tags are created regularly to indicate new official, stable release versions of lunarcoin.

##Testing

Testing and code review is the bottleneck for development; we get more pull requests than we can review and test. Please be patient and help out, and remember this is a security-critical project where any mistake might cost people lots of money.
Automated Testing

Developers are strongly encouraged to write unit tests for new code, and to submit new unit tests for old code.

Unit tests for the core code are in src/test/. To compile and run them:

cd src; make -f makefile.unix test

##Installing

git clone https://github.com/lunarcoin/lunarcoin.git
cd lunarcoin/src 
make -f makefile.unix 

##Run it

./lunarcoind
./lunarcoind getnewaddres ( get a Lunarcoin Wallet Address )
./lunarcoind setgenerate true 16 ( start Mining and Help the Network to get faster ( 16 is a value you can change and make Higer or Lower ) )
./lunarcoind getmininginfo ( Watch the Hashspeed ( Mining Speed ) )








