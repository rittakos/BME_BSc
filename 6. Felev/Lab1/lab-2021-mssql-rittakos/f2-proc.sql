

create or alter procedure CheckInvoice 
    @invoiceid int                    
as

begin tran                          
set transaction isolation level repeatable read

declare @IAmount int
declare @OAmount int
declare @Name varchar(100)

declare @problem int = 0

declare c cursor 
for select II.Amount, II.Name, OI.Amount
	from InvoiceItem II, OrderItem OI
	where InvoiceID = @invoiceid and II.OrderItemID = OI.ID and II.Amount != OI.Amount

open c
fetch from c into @IAmount, @Name, @OAmount
while @@fetch_status = 0
begin
	print	'Difference: ' + @Name + 
			' (invoice: ' + convert(varchar(5), @IAmount) + 
			' order: ' + convert(varchar(5), @OAmount) + ')'
	set @problem = 1
	fetch next from c into @IAmount, @Name, @OAmount
end


close c
deallocate c
commit
return @problem