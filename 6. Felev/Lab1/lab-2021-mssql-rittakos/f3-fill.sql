update Invoice
set Invoice.ItemCount =	(select sum(InvoiceItem.Amount) 
						from InvoiceItem 
						where InvoiceItem.InvoiceID = Invoice.ID)