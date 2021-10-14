# ThemeTPlatform

Added GRPC framework for Server and multiple Clients Trading: 
* WPF has error when using grpc.tools, so separated to a new lib and called in WPF
* proto files should be added in project file, eg. 
	<ItemGroup>
        <Protobuf Include="Protos\greet.proto" GrpcServices="Client" />
    </ItemGroup>
	
* make sure the path is correct, else proto code may not be generated successfully

ThemeTP: the new trading system 
    integrates ATP/TT APIs	
    implement algos
