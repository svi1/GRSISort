TARGET = Root2Rad


CFLAGS += -fPIC
CFLAGS += `root-config --cflags --libs`

#COMP_STRING="Now Compling "
DICT_STRING="Now Making Dict for ${OBJ_COLOR}$< ${NO_COLOR}"

CAT=cat

.PHONY: all clean gone end



UTIL_STRING = "Finished compiling utilities"

all: $(TARGET) end

end:
	@printf "\r ${FIN_COLOR}%s${FIN_OBJ_COLOR}%-30s ${NO_COLOR}\n" $(UTIL_STRING) $^ ;

$(TARGET): $(TARGET).cxx
	@printf " ${COM_COLOR}%s ${OBJ_COLOR}%s${NO_COLOR}" $(COMP_STRING) $@ 
	@$(CXX) $^ $(CFLAGS) $(CPPFLAGS) -o$(TARGET) 2> temp.log || touch temp.errors
	@if test -e temp.errors; then \
		printf "\r ${COM_COLOR}%s${OBJ_COLOR}%-30s ${ERROR_COLOR}%*s${NO_COLOR}\n" $(COMP_STRING) $@ 10 $(ERROR_STRING) \
		&& $(CAT) temp.log && \
		printf "${ERROR_COLOR}%s\n${NO_COLOR}" ${PWD};  \
		elif test -s temp.log; then \
		printf "\r ${COM_COLOR}%s${OBJ_COLOR}%-30s ${WARN_COLOR}%*s${NO_COLOR}\n" $(COMP_STRING) $@ 10 $(WARN_STRING) \
		&& $(CAT) temp.log; \
		else printf "\r ${COM_COLOR}%s${OBJ_COLOR}%-30s ${OK_COLOR}%*s${NO_COLOR}\n" $(COMP_STRING) $@ 10  $(OK_STRING); \
		fi;
	@$(RM) -f temp.errors temp.log temp.comp
	@mv $@ $(GRSISYS)/bin/$@

clean:
	$(RM) $(TARGET) *~ *Dict* *so 
