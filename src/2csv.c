/* @brief Convert the Abstract Syntax Tree generated by mpc for the DBC file
 * into an equivalent CSV file.
 * @copyright Richard James Howe (2018)
 * @license MIT
 *
 * @bug No escape done on ',', '\t', or '\n'
 */
#include "libdbcc/util.h"
#include "libdbcc/2csv.h"
#include <assert.h>

static int msg2csv(dbc_can_msg_t *msg, FILE *o)
{
	assert(msg);
	assert(o);

	signal_t *multiplexor = NULL;
	for(size_t i = 0; i < msg->signal_count; i++) {
		char sv[64];
		const char *multi = "N/A";
		signal_t *sig = msg->sigs[i];
		if(sig->is_multiplexor) {
			if(multiplexor) {
				error("multiple multiplexor values detected (only one per CAN msg is allowed) for %s", msg->name);
				return -1;
			}
			multi = "multiplexor";
		}
		if(sig->is_multiplexed) {
			sprintf(sv, "%d", sig->switchval);
			multi = sv;
		}

		/* "MSG, ID, DLC, Signal, Start, Length, Endianess, Scaling, Offset, Minimum, Maximum, Signed, Units, Multiplexed */
		fprintf(o, "%s, %lu, %u, ", msg->name, msg->id, msg->dlc);
		fprintf(o, "%s, ", sig->name);
		fprintf(o, "%u, ", sig->start_bit);
		fprintf(o, "%u, ", sig->bit_length);
		fprintf(o, "%s, ", sig->endianess == endianess_motorola_e ? "motorola" : "intel");
		fprintf(o, "%g, ", sig->scaling);
		fprintf(o, "%g, ", sig->offset);
		fprintf(o, "%g, ", sig->minimum);
		fprintf(o, "%g, ", sig->maximum);
		fprintf(o, "%s, ", sig->is_signed ? "true" : "false");
		bool have_units = false;
		const char *units = sig->units;
		for(size_t i = 0; units[i]; i++)
			if(!isspace(units[i]))
				have_units = true;
		if(!have_units)
			units = "none";
		fprintf(o, "%s, ", units);
		fprintf(o, "%s, ", multi);

		const char *floating = "no";
		if (sig->is_floating) {
			assert(sig->sigval == 1 || sig->sigval == 2);
			floating = (sig->sigval == 1) ? "single" : "double";
		}

		fprintf(o, "%s, ", floating);
		fprintf(o, "\n");
	}

	return 0;
}

int dbc2csv(dbc_t *dbc, FILE *output)
{
	assert(dbc);
	assert(output);
	fprintf(output, "MSG, ID, DLC, Signal, Start, Length, Endianess, Scaling, Offset, Minimum, Maximum, Signed, Units, Multiplexed, Floating,\n");
	for (size_t i = 0; i < dbc->message_count; i++)
		if(msg2csv(dbc->messages[i], output) < 0)
			return -1;
	return 0;
}

