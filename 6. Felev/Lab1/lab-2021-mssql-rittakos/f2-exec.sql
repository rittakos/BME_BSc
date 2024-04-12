declare @invoiceID int

declare allInvoices cursor
for select ID 
	from Invoice

open allInvoices
fetch from allInvoices into @invoiceID
while @@fetch_status = 0
begin
	print 'InvoiceID: ' + convert(varchar(5), @invoiceID) 

	declare @checkresult int
	exec @checkresult = CheckInvoice @invoiceID

	if(@checkresult = 0)
		print 'Invoice ok'

	fetch next from allInvoices into @invoiceID
end

close allInvoices
deallocate allInvoices

