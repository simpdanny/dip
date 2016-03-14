# This file define the hardcoded solutions.
# Please refer to report for better comprehension.

HW = warmup p1 p2 bonus
.PHONY: all clean  

all: $(HW) $(OUTPUTDIR)
warmup:	flip
	@mkdir -p $(OUTPUTDIR)/warmup
	@echo "warmup"
	@$(BINDIR)/flip true false raw/sample1.raw $(OUTPUTDIR)/warmup/sample1.hor.raw 256 256
	@$(BINDIR)/flip false true raw/sample1.raw $(OUTPUTDIR)/warmup/sample1.ver.raw 256 256
	@$(call CONVERT,$(OUTPUTDIR)/warmup/sample1.hor.raw, $(OUTPUTDIR)/warmup/sample1.hor.png)
	@$(call CONVERT,$(OUTPUTDIR)/warmup/sample1.ver.raw, $(OUTPUTDIR)/warmup/sample1.ver.png)

p1: p1a p1b p1c p1d p1e
.PHONY: p1a p1b p1c p1d p1e 

p1a: histogram analyze
	@mkdir -p $(OUTPUTDIR)/p1a
	@echo "$@ working..."; 
	@( $(BINDIR)/histogram raw/sample1.raw 256 256 > $(OUTPUTDIR)/p1a/sample1.hist; \
	$(call MATLAB,$(OUTPUTDIR)/p1a/sample1.hist,$(OUTPUTDIR)/p1a/sample1.hist.png) \
	$(BINDIR)/histogram raw/sample2.raw 256 256 > $(OUTPUTDIR)/p1a/sample2.hist; \
	$(call MATLAB,$(OUTPUTDIR)/p1a/sample2.hist,$(OUTPUTDIR)/p1a/sample2.hist.png) \
	$(BINDIR)/p1a ; \
	$(call CONVERT,$(OUTPUTDIR)/p1a/sample2.mul3.raw,$(OUTPUTDIR)/p1a/sample2.mul3.png) \
	$(BINDIR)/analyze raw/sample1.raw $(OUTPUTDIR)/p1a/sample2.mul3.raw 256 256 | grep "PSNR" ; \
	) > $(OUTPUTDIR)/p1a/p1a.log 
	@echo "$@ -> logged in $(OUTPUTDIR)/$@/$@.log"; 

p1b: heq histogram analyze
	@mkdir -p $(OUTPUTDIR)/p1b
	@echo "$@ working...";
	@( $(BINDIR)/heq raw/sample2.raw $(OUTPUTDIR)/p1b/sample2.heq.raw 256 256; \
	$(call CONVERT,$(OUTPUTDIR)/p1b/sample2.heq.raw,$(OUTPUTDIR)/p1b/sample2.heq.png) \
	$(BINDIR)/analyze raw/sample1.raw $(OUTPUTDIR)/p1b/sample2.heq.raw 256 256 | grep "PSNR" ; \
	) > $(OUTPUTDIR)/p1b/p1b.log
	@echo "$@ -> logged in $(OUTPUTDIR)/$@/$@.log";

p1c: aheq analyze
	@mkdir -p $(OUTPUTDIR)/p1c
	@echo "$@ working...";
	@( for w in 1 2 5 10 20 25 30 40; do \
		echo "$< window half length = $$w" ; \
		$(BINDIR)/aheq raw/sample2.raw $(OUTPUTDIR)/p1c/sample2.aheq$$w.raw 256 256 $$w; \
		$(call CONVERT,$(OUTPUTDIR)/p1c/sample2.aheq$$w.raw,$(OUTPUTDIR)/p1c/sample2.aheq$$w.png) \
		$(BINDIR)/analyze raw/sample1.raw $(OUTPUTDIR)/p1c/sample2.aheq$$w.raw 256 256 | grep "PSNR" ;\
	done ;) > $(OUTPUTDIR)/p1c/p1c.log
	@echo "$@ -> logged in $(OUTPUTDIR)/$@/$@.log";

p1d: p1b p1c
	@mkdir -p $(OUTPUTDIR)/p1d
	@echo "$@ working...";
	@$(BINDIR)/histogram $(OUTPUTDIR)/p1b/sample2.heq.raw 256 256 > $(OUTPUTDIR)/p1d/sample2.heq.hist
	@$(call MATLAB,$(OUTPUTDIR)/p1d/sample2.heq.hist,$(OUTPUTDIR)/p1d/sample2.heq.hist.png) 
	@$(BINDIR)/histogram $(OUTPUTDIR)/p1c/sample2.aheq5.raw 256 256 > $(OUTPUTDIR)/p1d/sample2.aheq5.hist
	@$(call MATLAB,$(OUTPUTDIR)/p1d/sample2.aheq5.hist,$(OUTPUTDIR)/p1d/sample2.aheq5.hist.png) 
	@$(BINDIR)/histogram $(OUTPUTDIR)/p1c/sample2.aheq40.raw 256 256 > $(OUTPUTDIR)/p1d/sample2.aheq40.hist
	@$(call MATLAB,$(OUTPUTDIR)/p1d/sample2.aheq40.hist,$(OUTPUTDIR)/p1d/sample2.aheq40.hist.png) 
	@echo "$@ -> figures in $(OUTPUTDIR)/$@";

p1e: p1e_log p1e_exp p1e_plaw
p1e_log: log analyze
	@echo "$@ working..."
	@mkdir -p $(OUTPUTDIR)/p1e/$<;
	@( for parameter in 1 5 10 50 100 500;\
	do \
		echo "$< parameter = $$parameter"; \
		bin=$<; \
		out=$(OUTPUTDIR)/p1e/$$bin/sample2.$$bin.$$parameter.raw; \
		outpng=$(OUTPUTDIR)/p1e/$$bin/sample2.$$bin.$$parameter.png; \
		outhist=$(OUTPUTDIR)/p1e/$$bin/sample2.$$bin.$$parameter.hist; \
		outhistpng=$(OUTPUTDIR)/p1e/$$bin/sample2.$$bin.$$parameter.hist.png; \
		$(BINDIR)/$$bin raw/sample2.raw $$out 256 256 $$parameter; \
		$(call CONVERT,$$out,$$outpng) \
		$(BINDIR)/histogram $$out 256 256 > $$outhist; \
		$(call MATLAB,$$outhist,$$outhistpng)\
		$(BINDIR)/analyze raw/sample1.raw $$out 256 256 | grep "PSNR" ;\
	done ; ) > $(OUTPUTDIR)/p1e/$@.log
	@echo "$@ -> logged in $(OUTPUTDIR)/p1e/$@.log"
	@echo "$@ -> figures in $(OUTPUTDIR)/p1e/$<"
p1e_exp: exp analyze
	@echo "$@ working..."
	@mkdir -p $(OUTPUTDIR)/p1e/$<;
	@( for parameter in 1 5 10 50 100 500;\
	do \
		echo "$< parameter = $$parameter"; \
		bin=$<; \
		out=$(OUTPUTDIR)/p1e/$$bin/sample2.$$bin.$$parameter.raw; \
		outpng=$(OUTPUTDIR)/p1e/$$bin/sample2.$$bin.$$parameter.png; \
		outhist=$(OUTPUTDIR)/p1e/$$bin/sample2.$$bin.$$parameter.hist; \
		outhistpng=$(OUTPUTDIR)/p1e/$$bin/sample2.$$bin.$$parameter.hist.png; \
		$(BINDIR)/reverse raw/sample2.raw $$out 256 256;\
		$(BINDIR)/$$bin $$out $$out 256 256 $$parameter; \
		$(BINDIR)/reverse $$out $$out 256 256;\
		$(call CONVERT,$$out,$$outpng) \
		$(BINDIR)/histogram $$out 256 256 > $$outhist; \
		$(call MATLAB,$$outhist,$$outhistpng)\
		$(BINDIR)/analyze raw/sample1.raw $$out 256 256 | grep "PSNR" ;\
	done ; ) > $(OUTPUTDIR)/p1e/$@.log
	@echo "$@ -> logged in $(OUTPUTDIR)/p1e/$@.log"
	@echo "$@ -> figures in $(OUTPUTDIR)/p1e/$<"

p1e_plaw: plaw analyze
	@echo "$@ working..."
	@mkdir -p $(OUTPUTDIR)/p1e/$<;
	@( for parameter in 0.2 0.4 0.6 0.8 1.0 1.2;\
	do \
		echo "$< parameter = $$parameter";\
		bin=$<; \
		out=$(OUTPUTDIR)/p1e/$$bin/sample2.$$bin.$$parameter.raw; \
		outpng=$(OUTPUTDIR)/p1e/$$bin/sample2.$$bin.$$parameter.png; \
		outhist=$(OUTPUTDIR)/p1e/$$bin/sample2.$$bin.$$parameter.hist; \
		outhistpng=$(OUTPUTDIR)/p1e/$$bin/sample2.$$bin.$$parameter.hist.png; \
		$(BINDIR)/$$bin raw/sample2.raw $$out 256 256 $$parameter; \
		$(call CONVERT,$$out,$$outpng) \
		$(BINDIR)/histogram $$out 256 256 > $$outhist; \
		$(call MATLAB,$$outhist,$$outhistpng)\
		$(BINDIR)/analyze raw/sample1.raw $$out 256 256 | grep "PSNR" ;\
	done ;	) > $(OUTPUTDIR)/p1e/$@.log
	@echo "$@ -> logged in $(OUTPUTDIR)/p1e/$@.log"
	@echo "$@ -> figures in $(OUTPUTDIR)/p1e/$<"

bonus: heq plaw directional_median_filter
	@echo "$@ working..."
	@mkdir -p $(OUTPUTDIR)/$@;
	@$(BINDIR)/directional_median_filter raw/bonus.raw $(OUTPUTDIR)/bonus/bonus.raw 256 256 2
	$(call CONVERT,$(OUTPUTDIR)/bonus/bonus.raw,$(OUTPUTDIR)/bonus/bonus1.png)
	@$(BINDIR)/plaw $(OUTPUTDIR)/bonus/bonus.raw $(OUTPUTDIR)/bonus/bonus.raw 256 256 1.5
	$(call CONVERT,$(OUTPUTDIR)/bonus/bonus.raw,$(OUTPUTDIR)/bonus/bonus2.png)
	@$(BINDIR)/heq $(OUTPUTDIR)/bonus/bonus.raw $(OUTPUTDIR)/bonus/bonus.raw 256 256
	$(call CONVERT,$(OUTPUTDIR)/bonus/bonus.raw,$(OUTPUTDIR)/bonus/bonus3.png)
	@$(BINDIR)/plaw $(OUTPUTDIR)/bonus/bonus.raw $(OUTPUTDIR)/bonus/bonus.raw 256 256 0.7
	$(call CONVERT,$(OUTPUTDIR)/bonus/bonus.raw,$(OUTPUTDIR)/bonus/bonus4.png)
	@$(BINDIR)/lowpass_filter $(OUTPUTDIR)/bonus/bonus.raw $(OUTPUTDIR)/bonus/bonus.raw 256 256 1
	$(call CONVERT,$(OUTPUTDIR)/bonus/bonus.raw,$(OUTPUTDIR)/bonus/bonus5.png)
	@$(BINDIR)/lowpass_filter $(OUTPUTDIR)/bonus/bonus.raw $(OUTPUTDIR)/bonus/bonus.raw 256 256 2
	$(call CONVERT,$(OUTPUTDIR)/bonus/bonus.raw,$(OUTPUTDIR)/bonus/bonus6.png)
	@echo "$@ stored in $(OUTPUTDIR)/bonus/bonus.raw"


p2: p2a p2b p2cd
.PHONY: p2 p2a p2b p2cd
p2a: impulse_pollute analyze
	@mkdir -p $(OUTPUTDIR)/$@
	@echo "$@ denotes impulse noise by eye. Run analyzer to detecte saturation/dead rate."
	@( white_prob=$$( $(BINDIR)/analyze raw/sample3.raw raw/sample3.raw 256 256 | grep "White_Prob" | cut -d ' ' -f 3 ); \
	black_prob=$$( $(BINDIR)/analyze raw/sample3.raw raw/sample3.raw 256 256 | grep "Black_Prob" | cut -d ' ' -f 3  ); \
	echo "white prob: $$white_prob, black prob: $$black_prob";\
	$(BINDIR)/impulse_pollute raw/sample1.raw $(OUTPUTDIR)/$@/sample1.$@.raw 256 256 $$white_prob $$black_prob;\
	$(call CONVERT,$(OUTPUTDIR)/$@/sample1.$@.raw,$(OUTPUTDIR)/$@/sample1.$@.png) \
	echo "Polluted image store in $(OUTPUTDIR)/$@/sample1.$@.raw"; )

p2b: gaussian_pollute lowpass_filter analyze
	@mkdir -p $(OUTPUTDIR)/$@
	@echo "$@ denotes gaussian noise by eye. First lowpass-filtering it into psuedo-reference."
	@$(BINDIR)/lowpass_filter raw/sample4.raw $(OUTPUTDIR)/$@/sample4.$@.raw 256 256 3;
	@$(BINDIR)/lowpass_filter $(OUTPUTDIR)/$@/sample4.$@.raw $(OUTPUTDIR)/$@/sample4.$@.raw 256 256 5;
	@$(call CONVERT,$(OUTPUTDIR)/$@/sample4.$@.raw,$(OUTPUTDIR)/$@/sample4.$@.png)
	@echo "Filtered reference image stored into $(OUTPUTDIR)/$@/sample4.$@.raw";
	@( stddev=$$( $(BINDIR)/analyze $(OUTPUTDIR)/$@/sample4.$@.raw raw/sample4.raw 256 256 | grep "Stddev" | cut -d ' ' -f 3 ); \
	echo "Standard Deviation: $$stddev";\
	$(BINDIR)/gaussian_pollute raw/sample1.raw $(OUTPUTDIR)/$@/sample1.$@.raw 256 256 $$stddev;\
	$(call CONVERT,$(OUTPUTDIR)/$@/sample1.$@.raw,$(OUTPUTDIR)/$@/sample1.$@.png) \
	echo "Polluted image store in $(OUTPUTDIR)/$@/sample1.$@.raw"; )

p2cd: p2cd_impulse p2cd_gaussian
p2cd_impulse: p2a median_filter directional_median_filter
	@mkdir -p $(OUTPUTDIR)/p2cd/impulse;
	@( for parameter in 1 2 3 4; do \
		echo "$@ perform median_filter $$parameter ...";\
		$(BINDIR)/median_filter $(OUTPUTDIR)/p2a/sample1.p2a.raw $(OUTPUTDIR)/p2cd/impulse/sample1.mf$$parameter.raw 256 256 $$parameter;\
		$(call CONVERT,$(OUTPUTDIR)/p2cd/impulse/sample1.mf$$parameter.raw,$(OUTPUTDIR)/p2cd/impulse/sample1.mf$$parameter.png) \
		$(BINDIR)/analyze raw/sample1.raw $(OUTPUTDIR)/p2cd/impulse/sample1.mf$$parameter.raw 256 256 | grep "PSNR" ;\
		echo "$@ perform directional_median_filter $$parameter ..."; \
		$(BINDIR)/directional_median_filter $(OUTPUTDIR)/p2a/sample1.p2a.raw $(OUTPUTDIR)/p2cd/impulse/sample1.dmf$$parameter.raw 256 256 $$parameter;\
		$(call CONVERT,$(OUTPUTDIR)/p2cd/impulse/sample1.dmf$$parameter.raw,$(OUTPUTDIR)/p2cd/impulse/sample1.dmf$$parameter.png) \
		$(BINDIR)/analyze raw/sample1.raw $(OUTPUTDIR)/p2cd/impulse/sample1.dmf$$parameter.raw 256 256 | grep "PSNR" ;\
	done ) > $(OUTPUTDIR)/p2cd/impulse.log
	@echo "$@ -> logged into $(OUTPUTDIR)/p2cd/impulse.log";

p2cd_gaussian: p2b lowpass_filter
	@mkdir -p $(OUTPUTDIR)/p2cd/gaussian;
	@( for parameter in 1 2 3 4 5; do \
		echo "$@ perform lowpass_filter $$parameter ...";\
		$(BINDIR)/lowpass_filter $(OUTPUTDIR)/p2b/sample1.p2b.raw $(OUTPUTDIR)/p2cd/gaussian/sample1.lpf$$parameter.raw 256 256 $$parameter;\
		$(call CONVERT,$(OUTPUTDIR)/p2cd/gaussian/sample1.lpf$$parameter.raw,$(OUTPUTDIR)/p2cd/gaussian/sample1.lpf$$parameter.png) \
		$(BINDIR)/analyze raw/sample1.raw $(OUTPUTDIR)/p2cd/gaussian/sample1.lpf$$parameter.raw 256 256 | grep "PSNR" ;\
	done ) > $(OUTPUTDIR)/p2cd/gaussian.log
	@cp $(OUTPUTDIR)/p2cd/gaussian/sample1.lpf1.raw $(OUTPUTDIR)/p2cd/gaussian/sample1.lpf.1.raw
	@( for parameter in 1 2 3 4 5; do \
			echo "$@ perform lowpass_filter $$parameter times (equivalent to bigger kernel window)" ; \
			$(BINDIR)/lowpass_filter $(OUTPUTDIR)/p2cd/gaussian/sample1.lpf.$$(($$parameter)).raw $(OUTPUTDIR)/p2cd/gaussian/sample1.lpf.$$(($$parameter+1)).raw 256 256 1; \
			$(call CONVERT,$(OUTPUTDIR)/p2cd/gaussian/sample1.lpf.$$(($$parameter+1)).raw,$(OUTPUTDIR)/p2cd/gaussian/sample1.lpf.$$(($$parameter+1)).png) \
			$(BINDIR)/analyze raw/sample1.raw $(OUTPUTDIR)/p2cd/gaussian/sample1.lpf.$$(($$parameter+1)).raw 256 256 | grep "PSNR" ;\
		done ;\
	) >> $(OUTPUTDIR)/p2cd/gaussian.log
	@echo "$@ -> logged into $(OUTPUTDIR)/p2cd/gaussian.log";
	




###

